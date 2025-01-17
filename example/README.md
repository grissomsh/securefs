# securefs with Docker

This guide demonstrates how to use `securefs` within a Docker container to manage encrypted filesystems easily and securely.

## Manifest

* [Dockerfile](Dockerfile)
* [entrypoint.sh](entrypoint.sh)

## docker build

Use the `Dockerfile` to build the SecureFS image.

```bash
docker build -t securefs:v1 .
```

## docker run

Run the container.

### privileged mode
```bash
docker run --rm -d --privileged -e SECUREFS_PASSWORD=your-password -v /encrypted:/encrypted securefs:v1 sleep 360
```

### non-root mode

Enable FUSE mount by non-root user.

```bash
vim /etc/fuse.conf

...
# Allow non-root users to specify the allow_other or allow_root mount options.
user_allow_other
...
```

Docker run.

```bash
docker run --rm -it \
--device /dev/fuse \
--cap-add SYS_ADMIN \
--cap-add MKNOD \
--security-opt apparmor:unconfined \
-e SECUREFS_PASSWORD=your-password \
-v /encrypted:/encrypted \
securefs:v1 \
/bin/bash
```

## Verification

```bash
docker ps
CONTAINER ID   IMAGE         COMMAND                  CREATED          STATUS          PORTS     NAMES
<container_id>   securefs:v1   "/usr/local/bin/entr…"   43 seconds ago   Up 43 seconds             competent_johnson
 
docker exec -it <container_id> /bin/bash
 
findmnt -l | grep secure
/mnt/secure                     securefs                                                                                            fuse.securefs rw,nosuid,nodev,relatime,user_id=0,group_id=0
 
ll /mnt/secure/
total 4
drwxr-xr-x 2 root root 70 Jan 16 03:40 ./
drwxr-xr-x 1 root root 20 Jan 16 05:40 ../
 
echo "aaaabbbbb" > /mnt/secure/a.txt
 
ll /mnt/secure/
total 4
drwxr-xr-x 2 root root 70 Jan 16 03:40 ./
drwxr-xr-x 1 root root 20 Jan 16 05:40 ../
-rw-r--r-- 1 root root 10 Jan 16 05:45 a.txt
 
cat /mnt/secure/a.txt
aaaabbbbb
 
# exit from container
exit
 
# execute in node
ll /encrypted/
total 12
drwxr-xr-x  2 root root   70 Jan 16 03:40 ./
drwxr-xr-x 23 root root 4096 Jan 16 03:38 ../
-rw-r--r--  1 root root  570 Jan 16 03:39 .securefs.json
-rw-r--r--  1 root root   54 Jan 16 05:45 V6CCZUUT7KEPPIVABAW226RFRZZAQHT7VA

```