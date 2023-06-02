echo "=== Running build ==="
echo ""

sudo docker build -t struct-account-t .

sleep 2
echo ""
echo "=== Built Docker Image: struct-account-t ==="
echo ""
sleep 2

sudo docker run -dp 1024:1024 -ti struct-account-t


sleep 2
echo ""
echo "=== Container is now running, connect using: 'nc localhost 1024' ==="
echo "=== Or using pwntools: 'remote('localhost', 1024)'               ==="
echo ""
