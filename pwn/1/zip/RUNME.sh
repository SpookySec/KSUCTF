echo "=== Running build ==="
echo ""

sudo docker build -t ezrop .

sleep 2
echo ""
echo "=== Built Docker Image: ezrop ==="
echo ""
sleep 2

sudo docker run -dp 1024:1024 -ti ezrop

sleep 2
echo ""
echo "=== Container is now running, connect using: 'nc localhost 1024' ==="
echo "=== Or using pwntools: 'remote('localhost', 1024)'               ==="
echo ""
