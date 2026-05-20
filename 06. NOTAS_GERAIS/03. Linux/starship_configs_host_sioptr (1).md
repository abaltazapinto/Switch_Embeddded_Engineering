# Starship configs — Host Linux e VM SIOPTR

Data: 2026-05-20

Objetivo: guardar separadamente as configurações visuais do terminal para:

- **Host Linux**: máquina principal, utilizador `andre`
- **VM SIOPTR-KernelLab**: máquina VirtualBox, utilizador `abaltaza`

> Regra de segurança:
>
> ```bash
> cp ~/.config/starship.toml ~/.config/starship.toml.bak-$(date +%Y%m%d-%H%M%S)
> ```

---

# 1. Host Linux

## Identidade visual

```text
andre in ~
🕘 09:44 LINUX ➜
```

## Objetivo

O host deve ser identificado por:

- utilizador `andre`
- etiqueta `LINUX`
- relógio na segunda linha
- sem etiqueta `SIOPTR`, para não confundir com a VM

## Blocos importantes

> Atenção: no host existia uma configuração antiga com símbolos/logos que querias preservar.  
> Por isso, **não substituir o ficheiro inteiro sem confirmar primeiro**.

```toml
format = "$username$directory\n$time$character"

[username]
show_always = true
style_user = "bold 214"
format = "[$user]($style) "

[directory]
style = "bold green"
format = "[in](bold green) [$path]($style) "

[time]
disabled = false
format = "[🕘 $time](bold white) [LINUX](bold green) "
time_format = "%H:%M"

[character]
success_symbol = "[➜](bold green)"
error_symbol = "[✗](bold red)"
```

## Warnings ainda vistos no host

```text
[WARN] - (starship::config): Error in 'Status' at 'failure_symbol': Unknown key
[WARN] - (starship::config): Error in 'Battery' at 'style': Unknown key
```

Estes warnings indicam chaves antigas/incompatíveis no `starship.toml`.

Antes de corrigir, ver os blocos reais:

```bash
grep -n '^\[status\]' -A10 ~/.config/starship.toml
grep -n '^\[battery\]' -A10 ~/.config/starship.toml
```

Possível correção futura:

```toml
[status]
failure_style = "bold red"

[battery]
disabled = true
```

---

# 2. VM SIOPTR-KernelLab

## Identidade visual

```text
abaltaza in ~
🕘 09:41 SIOPTR-KERNEL-VM ➜
```

## Objetivo

A VM deve ser identificada por:

- utilizador `abaltaza`
- etiqueta forte `SIOPTR-KERNEL-VM`
- relógio na segunda linha
- seta limpa
- sem `abaltaza@abaltaza-VirtualBox`

## Configuração funcional da VM

```toml
format = """
$username [in](bold green) $directory
$time [ SIOPTR-KERNEL-VM ](bold red) $character
"""

add_newline = true

[username]
show_always = true
style_user = "bold 214"
style_root = "bold red"
format = "[$user]($style)"

[directory]
style = "bold green"
truncation_length = 3
truncate_to_repo = false
format = "[$path]($style)"

[time]
disabled = false
format = "[🕘 $time](bold white)"
time_format = "%H:%M"

[git_branch]
symbol = " "
style = "bold purple"
format = "on [$symbol$branch]($style) "

[git_status]
style = "bold red"
format = "[$all_status$ahead_behind]($style) "

[character]
success_symbol = "[➜](bold green)"
error_symbol = "[✗](bold red)"
```

---

# 3. Aplicar configuração completa na VM SIOPTR

Na VM, correr:

```bash
mkdir -p ~/.config
cp ~/.config/starship.toml ~/.config/starship.toml.bak-before-sioptr-final 2>/dev/null

cat > ~/.config/starship.toml <<'EOF'
format = """
$username [in](bold green) $directory
$time [ SIOPTR-KERNEL-VM ](bold red) $character
"""

add_newline = true

[username]
show_always = true
style_user = "bold 214"
style_root = "bold red"
format = "[$user]($style)"

[directory]
style = "bold green"
truncation_length = 3
truncate_to_repo = false
format = "[$path]($style)"

[time]
disabled = false
format = "[🕘 $time](bold white)"
time_format = "%H:%M"

[git_branch]
symbol = " "
style = "bold purple"
format = "on [$symbol$branch]($style) "

[git_status]
style = "bold red"
format = "[$all_status$ahead_behind]($style) "

[character]
success_symbol = "[➜](bold green)"
error_symbol = "[✗](bold red)"
EOF

grep -q 'starship init bash' ~/.bashrc || echo 'eval "$(starship init bash)"' >> ~/.bashrc
source ~/.bashrc
```

---

# 4. Aplicar apenas o relógio + LINUX no host

No host, correr só se já existir `$time` no prompt:

```bash
cp ~/.config/starship.toml ~/.config/starship.toml.bak-before-linux-inside-time

python3 - <<'PY'
from pathlib import Path
import re

p = Path.home() / ".config" / "starship.toml"
text = p.read_text()

text = re.sub(
    r'\[time\][\s\S]*?(?=\n\[|\Z)',
    '[time]\ndisabled = false\nformat = "[🕘 $time](bold white) [LINUX](bold green) "\ntime_format = "%H:%M"\n',
    text
)

p.write_text(text)
PY

source ~/.bashrc
```

---

# 5. Diagnóstico rápido

## Ver o format principal

```bash
grep -n '^format' -A5 ~/.config/starship.toml
```

## Ver blocos relevantes

```bash
grep -n '^\[username\]' -A10 ~/.config/starship.toml
grep -n '^\[directory\]' -A10 ~/.config/starship.toml
grep -n '^\[time\]' -A10 ~/.config/starship.toml
grep -n '^\[character\]' -A10 ~/.config/starship.toml
```

## Ver se Starship está ativo

```bash
grep 'starship init bash' ~/.bashrc
```

## Recarregar

```bash
source ~/.bashrc
```

---

# 6. Reverter

## Listar backups

```bash
ls -la ~/.config/starship.toml.bak*
```

## Reverter para um backup

```bash
cp ~/.config/starship.toml.bak-NOME ~/.config/starship.toml
source ~/.bashrc
```

---

# 7. Regra de ouro

Nunca aplicar comandos do host dentro da VM, nem comandos da VM no host.

Verifica sempre o prompt antes de mexer:

```text
andre     → host Linux
abaltaza  → VM SIOPTR
```
