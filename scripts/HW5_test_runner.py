#!/usr/bin/env python3
import sys
import os
import json
import subprocess
import difflib


def load_manifest(path):
    with open(path, 'r', encoding='utf-8') as f:
        return json.load(f)


def collect_tests(manifest):
    tests = []
    for question, cases in manifest.items():
        for case in cases:
            case = dict(case)
            case['question'] = question
            tests.append(case)
    return tests


def read_text(path):
    with open(path, 'r', encoding='utf-8') as f:
        return f.read()


def build_input(case):
    if 'input' in case:
        return read_text(case['input'])
    if 'input_parts' in case:
        return ''.join(read_text(p) for p in case['input_parts'])
    raise ValueError(f"Case missing input/input_parts: {case}")


def run_test(exe_path, case):
    input_data = build_input(case)
    expected = read_text(case['output'])

    try:
        proc = subprocess.run(
            [exe_path],
            input=input_data,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            check=False,
        )
    except Exception as e:
        return False, f"Error running '{exe_path}': {e}"

    actual = proc.stdout
    if actual == expected:
        return True, None

    diff = difflib.unified_diff(
        expected.splitlines(keepends=True),
        actual.splitlines(keepends=True),
        fromfile='expected',
        tofile='actual',
    )
    return False, ''.join(diff)


def main():
    if len(sys.argv) != 3:
        print('Usage: python3 HW5_test_runner.py <submission_dir> <manifest.json>')
        sys.exit(1)

    submission_dir = sys.argv[1]
    manifest_path = sys.argv[2]

    if not os.path.isdir(submission_dir):
        print(f'Submission directory not found: {submission_dir}')
        sys.exit(1)
    if not os.path.isfile(manifest_path):
        print(f'Manifest not found: {manifest_path}')
        sys.exit(1)

    manifest = load_manifest(manifest_path)
    tests = collect_tests(manifest)
    failures = 0

    for case in tests:
        question = case['question']
        executable_name = case.get('executable') or question.lower().replace('Q', 'hw5_q')
        exe_path = os.path.join(submission_dir, executable_name)
        label = case.get('name') or case.get('input') or '+'.join(case.get('input_parts', []))

        if not os.path.isfile(exe_path):
            print(f'❌ Missing executable for {question}: {exe_path}')
            failures += 1
            continue

        ok, info = run_test(exe_path, case)
        if ok:
            print(f'✅ PASS: {question} :: {label}')
        else:
            print(f'❌ FAIL: {question} :: {label}')
            print(info, end='')
            failures += 1

    if failures:
        print(f'\n🚨 {failures} test(s) failed.')
        sys.exit(1)

    print('\n🎉 All tests passed.')
    sys.exit(0)


if __name__ == '__main__':
    main()
