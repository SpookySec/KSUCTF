FROM ubuntu:23.10


RUN useradd -d /home/ctf/ -m -p ctf -s /bin/bash ctf
RUN echo "ctf:ctf" | chpasswd

WORKDIR /home/ctf

COPY main .
COPY flag.txt .
COPY ynetd .

USER ctf

EXPOSE 1024
CMD ["./ynetd", "-p", "1024", "./main"]
