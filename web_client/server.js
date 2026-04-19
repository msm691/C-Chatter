const WebSocket = require('ws');
const net = require('net');

const WS_PORT = 8081;
const C_PORT = 8080;
const C_HOST = '127.0.0.1';

const LOGIN_REQ = 1;
const MSG_REQ = 2;
const MAX_NAME_LENGTH = 32;
const MAX_MSG_LENGTH = 512;
const PAYLOAD_SIZE = MAX_NAME_LENGTH + MAX_MSG_LENGTH;
const HEADER_SIZE = 8;

const wss = new WebSocket.Server({ port: WS_PORT });

wss.on('connection', (ws) => {
    console.log('🌐 Nouveau client Web connecté.');

    const tcpClient = new net.Socket();
    tcpClient.connect(C_PORT, C_HOST, () => {
        console.log('🔗 Proxy connecté au serveur C.');
    });

    tcpClient.on('data', (data) => {
        if (data.length >= HEADER_SIZE) {
            const payload = data.slice(HEADER_SIZE);
            if (payload.length >= PAYLOAD_SIZE) {
                const sender = payload.slice(0, MAX_NAME_LENGTH).toString('utf8').replace(/\0/g, '');
                const text = payload.slice(MAX_NAME_LENGTH, PAYLOAD_SIZE).toString('utf8').replace(/\0/g, '');
                
                ws.send(JSON.stringify({ sender, text }));
            }
        }
    });

    tcpClient.on('close', () => ws.close());
    tcpClient.on('error', () => ws.close());

    ws.on('message', (message) => {
        try {
            const data = JSON.parse(message);
            const packetType = data.type === 'login' ? LOGIN_REQ : MSG_REQ;
            const username = data.username || "WebUser";
            const text = data.text || "";

            const buffer = Buffer.alloc(HEADER_SIZE + PAYLOAD_SIZE);

            buffer.writeUInt16LE(packetType, 0);
            buffer.writeUInt32LE(PAYLOAD_SIZE, 4);

            buffer.write(username.substring(0, MAX_NAME_LENGTH - 1), HEADER_SIZE, 'utf8');
            
            const textWithNewline = text + '\n';
            buffer.write(textWithNewline.substring(0, MAX_MSG_LENGTH - 1), HEADER_SIZE + MAX_NAME_LENGTH, 'utf8');

            tcpClient.write(buffer);
        } catch (e) {
            console.error('Message web invalide.', e);
        }
    });

    ws.on('close', () => tcpClient.destroy());
});

console.log(`🚀 Proxy Node.js démarré sur ws://localhost:${WS_PORT}`);