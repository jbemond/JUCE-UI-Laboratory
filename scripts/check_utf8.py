#!/usr/bin/env python3
"""Vérifie que les fichiers texte du projet sont réellement encodés en UTF-8."""
from pathlib import Path

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
        for marker in BAD:
            if marker in text:
                errors.append(f"{path.relative_to(ROOT)} : séquence suspecte {marker!r}")
    except UnicodeDecodeError as exc:
        errors.append(f"{path.relative_to(ROOT)} : encodage non UTF-8 : {exc}")
if errors:
    print("\n".join(errors))
    raise SystemExit(1)
print("Contrôle UTF-8 : OK")
