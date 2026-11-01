#!/usr/bin/env python3
"""Vérifie que les fichiers texte du projet sont réellement encodés en UTF-8."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
EXTENSIONS = {".cpp", ".h", ".hpp", ".md", ".txt", ".cmake", ".yml", ".yaml", ".json", ".py", ".ps1"}
BAD = ("Ã©", "Ã¨", "Ãª", "Ã ", "Ã§", "Ã´", "Â©", "â€™", "â€“", "â€”", "�")
errors = []
for path in ROOT.rglob("*"):
    if not path.is_file() or any(part in {".git", "build", ".vs"} or part.startswith("build-") for part in path.relative_to(ROOT).parts):
        continue
    if path.suffix not in EXTENSIONS and path.name not in {"CMakeLists.txt", ".gitattributes", ".gitignore"}:
        continue
    try:
        text = path.read_bytes().decode("utf-8", errors="strict")
        if path.suffix in {".cpp", ".h", ".hpp"}:
            # JUCE 8 / C++17: raw non-ASCII char* literals are not UTF-8 decoded
            # automatically by juce::String. Require explicit fromUTF8(u8"...").
            literal_pattern = re.compile(r'(?:u8)?"(?:\\\\.|[^"\\\\])*"', re.DOTALL)
            for match in literal_pattern.finditer(text):
                literal = match.group(0)
                if any(ord(ch) > 127 for ch in literal):
                    prefix = text[max(0, match.start() - 30):match.start()]
                    if not prefix.endswith("juce::String::fromUTF8("):
                        errors.append(f"{path.relative_to(ROOT)} : littéral accentué sans fromUTF8 : {literal[:60]}")
        for marker in BAD:
            if marker in text:
                errors.append(f"{path.relative_to(ROOT)} : séquence suspecte {marker!r}")
    except UnicodeDecodeError as exc:
        errors.append(f"{path.relative_to(ROOT)} : encodage non UTF-8 : {exc}")
if errors:
    print("\n".join(errors))
    raise SystemExit(1)
print("Contrôle UTF-8 : OK")
