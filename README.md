# MQTT Server Setup

This repository contains the configuration for a Mosquitto MQTT broker that can be deployed both locally and on AWS.

## Local Setup

1. Install Docker and Docker Compose
2. Start the MQTT broker:
   ```bash
   docker-compose up -d
   ```

## Installation on Ubuntu

1. Update the package list:
   ```bash
   sudo apt update
   ```

2. Install Docker:
   ```bash
   sudo apt install -y docker.io
   sudo systemctl start docker
   sudo systemctl enable docker
   ```

3. Install Docker Compose:
   ```bash
   sudo apt install -y docker-compose
   ```

4. Add your user to the docker group:
   ```bash
   sudo usermod -aG docker $USER
   ```

5. Log out and back in to apply group changes.

## Installation on Fedora

1. Install Docker:
   ```bash
   sudo dnf -y install dnf-plugins-core
   sudo dnf config-manager --add-repo https://download.docker.com/linux/fedora/docker-ce.repo
   sudo dnf install docker-ce docker-ce-cli containerd.io docker-compose-plugin
   ```

2. Start and enable Docker:
   ```bash
   sudo systemctl start docker
   sudo systemctl enable docker
   ```

3. Add your user to the docker group:
   ```bash
   sudo usermod -aG docker $USER
   ```

4. Log out and back in to apply group changes.

## Testing the Server
You can test the server using mosquitto clients:

```bash
# Install mosquitto clients
sudo apt-get install mosquitto-clients

# Subscribe to a topic
mosquitto_sub -h localhost -t "test/topic"

# Publish to a topic (in another terminal)
mosquitto_pub -h localhost -t "test/topic" -m "Hello MQTT"
```

## AWS Deployment Instructions

1. Launch an EC2 instance:
   - Choose Ubuntu Server 20.04 LTS
   - Select t2.micro for testing (adjust based on needs)
   - Configure Security Group:
     * Allow TCP 1883 (MQTT)
     * Allow TCP 8883 (MQTT over TLS)
     * Allow TCP 9001 (WebSocket)
     * Allow TCP 22 (SSH)

2. SSH into your EC2 instance:
   ```bash
   ssh -i your-key.pem ubuntu@your-ec2-ip
   ```

3. Install Docker and Docker Compose:
   ```bash
   sudo apt-get update
   sudo apt-get install docker.io docker-compose -y
   ```

4. Clone this repository and deploy:
   ```bash
   git clone <repository-url>
   cd mqtt-server
   sudo docker-compose up -d
   ```

## Security Considerations

1. For production:
   - Disable anonymous access
   - Enable TLS
   - Set up username/password authentication
   - Use AWS security groups effectively

2. Generate SSL certificates:
   ```bash
   # Generate CA key and certificate
   openssl genrsa -out ca.key 2048
   openssl req -new -x509 -days 365 -key ca.key -out ca.crt

   # Generate server key and certificate
   openssl genrsa -out server.key 2048
   openssl req -new -key server.key -out server.csr
   openssl x509 -req -days 365 -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt
   ```

## Monitoring

- Check logs:
  ```bash
  docker-compose logs -f
  ```

- Monitor connections:
  ```bash
  docker exec mqtt_broker mosquitto_sub -v -t '$SYS/#'
  ```
