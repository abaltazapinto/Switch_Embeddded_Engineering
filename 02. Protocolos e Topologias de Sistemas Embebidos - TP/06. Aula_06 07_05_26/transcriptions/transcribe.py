from faster_whisper import WhisperModel
import sys
from pathlib import Path

def format_ts(seconds: float) -> str:
    ms = int(round(seconds * 1000))
    h = ms // 3_600_000
    ms %= 3_600_000
    m = ms // 60_000
    ms %= 60_000
    s = ms // 1000
    ms %= 1000
    return f"{h:02}:{m:02}:{s:02},{ms:03}"

if len(sys.argv) < 2:
    print("Uso: python transcribe.py <ficheiro_audio_ou_video>")
    sys.exit(1)

input_file = Path(sys.argv[1])
output_file = input_file.with_suffix(".srt")

model = WhisperModel("small", device="cuda", compute_type="float16")

segments, info = model.transcribe(
    str(input_file),
    language="pt",
    vad_filter=True,
    beam_size=5,
)

with open(output_file, "w", encoding="utf-8") as f:
    for i, segment in enumerate(segments, start=1):
        f.write(f"{i}\n")
        f.write(f"{format_ts(segment.start)} --> {format_ts(segment.end)}\n")
        f.write(segment.text.strip() + "\n\n")

print(f"SRT criado: {output_file}")
print(f"Língua: {info.language} | Prob: {info.language_probability:.3f}")
