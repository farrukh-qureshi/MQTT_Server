#!/bin/bash

# Create certificates directory if it doesn't exist
mkdir -p certs
cd certs

# Generate CA key and certificate
openssl genrsa -out ca.key 2048
openssl req -new -x509 -days 365 -key ca.key -out ca.crt -subj "/CN=MQTT CA"

# Generate server key and certificate signing request
openssl genrsa -out server.key 2048
openssl req -new -key server.key -out server.csr -subj "/CN=mqtt.server"

# Sign the server certificate with our CA
openssl x509 -req -days 365 -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt

# Set proper permissions
chmod 644 ca.crt server.crt
chmod 600 ca.key server.key

echo "Certificates generated successfully!"
