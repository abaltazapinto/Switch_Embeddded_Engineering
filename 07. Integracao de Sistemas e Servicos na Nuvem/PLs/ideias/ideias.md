Sim — e agora já tens **a espinha dorsal disso a funcionar**. O que acabaste de provar é bem mais interessante do que um simples exercício de MQTT.

Neste momento tens:

```text
Porto Digital / FIWARE
        ↓
CT 200 — ct-fiware-sensor
        ↓
   MQTT / Mosquitto
        ↓
CT 300 — ct-local-cloud
```

E na imagem já estás a receber dados reais como:

```text
Aliados
  temperature       17.1 °C
  relativeHumidity  93.7 %
  windSpeed         3.6
  latitude          41.147...
  longitude        -8.611...

Arca d'Água
  temperature       16.7 °C
  relativeHumidity  93.6 %

Hospital S. António
  temperature       16.9 °C
  relativeHumidity  94.0 %
```

Ou seja: **sim, podes transformar isto num homelab de dados urbanos do Porto**.

Uma arquitetura muito porreira seria:

```text
                    PORTO DIGITAL / FIWARE
                             │
                             ▼
                  CT 200 — Data Collector
                     Python / MQTT
                             │
                             ▼
                       Mosquitto
                             │
           ┌─────────────────┴────────────────┐
           ▼                                  ▼
 CT 300 — Data Platform              VM 100 — Edge/k3s
 ├── InfluxDB / CrateDB              ├── Kubernetes
 ├── Grafana                         ├── APIs
 ├── historical data                 └── services
 └── alerts
```

Depois no **Grafana** podes ter dashboards tipo:

- 🌡️ temperatura por estação;
- 💧 humidade;
- 🌬️ velocidade do vento;
- ☁️ precipitação;
- 🫁 PM2.5 / PM10 / NO₂ / O₃;
- AQI por zona;
- mapa das estações usando latitude/longitude;
- evolução das últimas 24 h / 7 dias / mês;
- comparação `Aliados vs Bolhão vs Arca d'Água`;
- alertas do género `PM2.5 > limite` ou `temperatura > X`.

E há algo ainda melhor: já estás a receber:

```text
dateObserved
last_mqtt_update
```

Portanto consegues distinguir **quando a estação mediu o dado** de **quando o teu sistema o recebeu**. Isso permite estudar atraso, estações stale, qualidade dos dados, disponibilidade, etc.

### Isto dava um projeto de portefólio muito bom

Eu até lhe daria um nome próprio, por exemplo:

**Porto Urban Edge Observatory**

ou:

**Porto Smart City Homelab**

E no GitHub poderias apresentar:

```text
Proxmox VE
SDN
LXC / KVM
Python
FIWARE
MQTT
Docker
k3s
Grafana
Time-series database
Monitoring
```

Isso começa a ficar diretamente relevante para **Edge/IoT, DevOps, SRE, Smart Cities e Industrial IoT**.

Só uma ressalva: alguns dados FIWARE que viste estão marcados como `stale`, portanto o teu sistema deve mostrar claramente **frescura/idade dos dados** e não assumir que todas as estações publicam continuamente. Isso, aliás, torna o projeto tecnicamente mais interessante.

E podemos aproveitar o **resto do Lab 3 para começar exatamente esse homelab**, em vez de fazer comandos só para “passar o guião”.
