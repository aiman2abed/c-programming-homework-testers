import re
from pathlib import Path

DUMP_FILE = "test_files_hw3_dump.txt"
OUTPUT_ROOT = "."

HEADER_RE = re.compile(r"^==>\s+\./(hw3_q(\d+))/(input|output)([^<]*)\s+<==$")

def normalize_filename(question_num: str, io_type: str, suffix: str) -> str:
    """
    Convert raw filenames like:
      input1.txt              -> q1_input1.txt
      input1_official.txt     -> q1_input1_official.txt
      input_official.txt      -> q1_input_official.txt
      output3.txt             -> q1_output3.txt
      output2_official.txt    -> q1_output2_official.txt
    """
    suffix = suffix.strip()

    # remove leading dot if present accidentally
    if suffix.startswith("."):
        suffix = suffix[1:]

    # examples of suffix values:
    # "1.txt"
    # "1_official.txt"
    # "_official.txt"

    if suffix == "_official.txt":
        return f"q{question_num}_{io_type}_official.txt"

    m_num_official = re.fullmatch(r"(\d+)_official\.txt", suffix)
    if m_num_official:
        n = m_num_official.group(1)
        return f"q{question_num}_{io_type}{n}_official.txt"

    m_num = re.fullmatch(r"(\d+)\.txt", suffix)
    if m_num:
        n = m_num.group(1)
        return f"q{question_num}_{io_type}{n}.txt"

    # fallback: preserve whatever strange suffix exists
    cleaned = suffix.replace("/", "_")
    if cleaned.startswith("_"):
        return f"q{question_num}_{io_type}{cleaned}"
    return f"q{question_num}_{io_type}_{cleaned}"

def parse_dump(text: str):
    """
    Returns a list of tuples:
      (question_num, io_type, raw_rel_path, content)
    """
    lines = text.splitlines()
    entries = []

    current_meta = None
    current_content = []

    for line in lines:
        header_match = HEADER_RE.match(line)

        if header_match:
            # flush previous block
            if current_meta is not None:
                qnum, io_type, raw_rel_path = current_meta
                content = "\n".join(current_content).rstrip("\n")
                entries.append((qnum, io_type, raw_rel_path, content))

            folder_name = header_match.group(1)   # hw3_q1
            qnum = header_match.group(2)          # 1
            io_type = header_match.group(3)       # input/output
            suffix = header_match.group(4)        # e.g. 1.txt, _official.txt

            raw_rel_path = f"{folder_name}/{io_type}{suffix}"
            current_meta = (qnum, io_type, raw_rel_path)
            current_content = []
        else:
            # ignore duplicated title lines like "==> ./test_files_hw3_dump.txt <=="
            if line.strip() == "==> ./test_files_hw3_dump.txt <==":
                continue
            if current_meta is not None:
                current_content.append(line)

    # flush last block
    if current_meta is not None:
        qnum, io_type, raw_rel_path = current_meta
        content = "\n".join(current_content).rstrip("\n")
        entries.append((qnum, io_type, raw_rel_path, content))

    return entries

def main():
    dump_path = Path(DUMP_FILE)
    if not dump_path.exists():
        raise FileNotFoundError(f"Dump file not found: {dump_path}")

    text = dump_path.read_text(encoding="utf-8", errors="replace")
    entries = parse_dump(text)

    if not entries:
        print("No HW3 test entries found.")
        return

    created = []

    for qnum, io_type, raw_rel_path, content in entries:
        # Extract suffix from raw path
        # raw_rel_path format: hw3_q1/input1.txt or hw3_q1/input_official.txt
        raw_name = Path(raw_rel_path).name  # input1.txt, output2_official.txt, etc.
        assert raw_name.startswith(io_type)
        suffix = raw_name[len(io_type):]    # 1.txt / _official.txt / 2_official.txt

        normalized_name = normalize_filename(qnum, io_type, suffix)

        target_dir = Path(OUTPUT_ROOT) / f"Q{qnum}" / io_type
        target_dir.mkdir(parents=True, exist_ok=True)

        target_file = target_dir / normalized_name
        target_file.write_text(content + "\n", encoding="utf-8")
        created.append(str(target_file))

    print("Created files:")
    for path in created:
        print(path)

if __name__ == "__main__":
    main()