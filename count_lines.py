from pathlib import Path
import math

def get_paths() -> list[str]:
    file_extensions = [".cpp", ".c++", ".cc", ".cp", ".C"]
    cdir = Path(__file__).resolve().parent
    return [str(path) for path in cdir.rglob("*") if path.is_file() and any([str(path).endswith(e) for e in file_extensions])]

def main() -> None:
    paths = get_paths()
    line_counts = dict()
    for path in paths:
        end = "/".join(path.split("/")[-3:])
        with open(path, "r") as file:
            lines = [line for line in file]

        line_counts[end] = len(lines)
    
    print(f"{'-' * 50}\nTotal lines: {sum(line_counts.values())}\n{'-' * 50}")
    print(f"Lines per file: {round(sum(line_counts.values()) / len(line_counts.values()))}\n{'-' * 50}")
    
    max_val, min_val = -math.inf, math.inf
    max_key, min_key = "", ""
    for k, v in line_counts.items():
        if v > max_val:
            max_val = v
            max_key = k
        if v < min_val:
            min_val = v
            min_key = k

    print(f"Largest file: {max_key} - {max_val} lines\n{'-' * 50}")
    print(f"Smallest file: {min_key} - {min_val} lines\n{'-' * 50}")

if __name__ == "__main__":
    main()
