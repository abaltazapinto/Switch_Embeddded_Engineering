Estou a preparar o ambiente Linux/VirtualBox para a cadeira SIOPTR.

Objetivo:
Criar uma VM dedicada para SIOPTR, separada da VM de Topologias, porque SIOPTR vai mexer com kernel, módulos, GRUB, MOKER, trace-cmd/kernelshark e coisas potencialmente destrutivas.

Estado atual do host:
- Host principal: Linux
- Kernel do host confirmado:
  uname -r
  → 6.17.0-23-generic

VirtualBox no host:
- VirtualBox instalado e a funcionar.
- Headers do kernel instalados:
  linux-headers-6.17.0-23-generic
- O módulo vboxdrv inicialmente não existia, mas depois de instalar VirtualBox/DKMS ficou funcional.
- Teste:
  sudo modprobe vboxdrv
  → voltou ao prompt sem erro, portanto OK.

Espaço em disco:
- df -h mostrou cerca de 288G no /, com ~210G usados e ~63G livres.
- Foi descoberto que ~/.local/share/Trash tinha ~65G.
- Também havia:
  ~/.cache ~17G
  ~/Documents ~58G
  ~/linux-kernel ~2.8G
  ~/Kathara ~443M
- Conclusão: Kathará não era o maior problema; o Trash era.

Estratégia de VMs:
Foi decidido usar:
- 1 VM base limpa
- clones completos para cada cadeira

Arquitetura:
Ubuntu-Base-24.04-CLEAN   ← base limpa, não usar para trabalhos
├── SIOPTR-KernelLab       ← para SIOPTR/kernel/MOKER/módulos
└── Topologias&Protocolos - Embedded ← para Kathará/topologias/redes

ISO usada:
- ubuntu-24.04.4-desktop-amd64.iso

Criação da base:
- A instalação manual deu problemas/ciclo com Live ISO.
- Solução final: recriar a VM usando Unattended Installation.
- Nome final da base:
  Ubuntu-Base-24.04-CLEAN
- Configuração:
  RAM: 4096 MB
  CPU: 2
  Disco: 80 GB dinâmico
  EFI: false
  ISO: Ubuntu 24.04.4
  Unattended install: ligado
- Utilizador criado automaticamente:
  abaltaza
- A base arrancou corretamente e recebeu updates.

Problema gráfico:
- O Ubuntu/VirtualBox mostrou erro:
  vmwgfx seems to be running on an unsupported hypervisor
- Foi corrigido via VBoxManage.
- Configuração gráfica funcional:
  Graphics Controller: VBoxVGA
  VRAM: 128 MB
  3D Acceleration: disabled
- Comando usado para verificar:
  VBoxManage showvminfo "Ubuntu-Base-24.04-CLEAN" | grep -Ei "graphics|vram|3d"
- Resultado esperado:
  VRAM size: 128MB
  Graphics Controller: VBoxVGA
  3D Acceleration: disabled

Clones criados:
1. SIOPTR-KernelLab
   - Full Clone
   - novo MAC
   - Powered Off
   - Disco: 80 GB
   - RAM: 4096 MB
   - CPU: 2
   - Graphics Controller: VBoxVGA
   - VRAM: 128 MB
   - 3D disabled

2. Topologias&Protocolos - Embedded
   - Full Clone
   - novo MAC
   - Powered Off inicialmente
   - Já arrancou e está a ser usado para Topologias/Kathará

Estado da VM Topologias:
- Está funcional.
- Internet funciona.
- apt update funciona.
- Foi instalada JetBrainsMono Nerd Font.
- Terminal foi configurado visualmente com fundo escuro e texto verde.
- Houve tentativa de configurar clipboard bidirecional.
- Shared Clipboard foi colocado como Bidirectional, mas copy/paste ainda estava problemático.
- Guest packages instalados:
  virtualbox-guest-utils
  virtualbox-guest-x11
  virtualbox-guest-utils-hwe
  virtualbox-guest-x11-hwe
- Mesmo assim, Ctrl+V no terminal mostrava ^V.
- Nota importante: em terminal Linux, paste é Ctrl+Shift+V, não Ctrl+V.
- Se clipboard continuar a falhar, usar comandos manuais ou resolver depois.

Objetivo para o novo chat:
Quero agora preparar a VM SIOPTR-KernelLab rapidamente e corretamente para a cadeira SIOPTR.

Prioridade:
1. Arrancar SIOPTR-KernelLab.
2. Confirmar login e internet.
3. Fazer snapshot inicial.
4. Instalar ferramentas mínimas.
5. Preparar ambiente para kernel/MOKER/LKM.
6. Evitar mexer no host principal.

Preferência de resposta:
Quero um passo de cada vez, estilo mentor sénior de Embedded/Linux, explicando objetivo, raciocínio, pitfalls e pergunta de decisão.



---

# +verificacao 

hostnamectl
uname -r
ip a
ping -c 3 8.8.8.8
ping -c 3 ubuntu.com
df -h

# Isto vlaida 

| Verificação       | O que prova                            |
| ----------------- | -------------------------------------- |
| `hostnamectl`     | Nome da VM, versão Ubuntu, arquitetura |
| `uname -r`        | Kernel atual da VM, não do host        |
| `ip a`            | Interface de rede ativa                |
| `ping 8.8.8.8`    | Internet por IP                        |
| `ping ubuntu.com` | DNS funcional                          |
| `df -h`           | Disco disponível dentro da VM          |
