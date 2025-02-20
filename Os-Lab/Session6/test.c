#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#define device_path "/dev/saman_headphone"
#define IOCTL_MUTE _IO('i', 1)
#define IOCTL_UNMUTE _IO('i', 2)
#define IOCTL_SET_VOLUME _IOW('i', 3, int)
#define IOCTL_GET_VOLUME _IOR('i', 4, int)

void set_volume(int fd, int volume) {
    ioctl(fd, IOCTL_SET_VOLUME, &volume);
}

int get_volume(int fd) {
    int volume;
    ioctl(fd, IOCTL_GET_VOLUME, &volume);
    return volume;
}

void mute(int fd) {
    ioctl(fd, IOCTL_MUTE);
}

void unmute(int fd) {
    ioctl(fd, IOCTL_UNMUTE);
}

void play(const char *message) {
    int fd = open(device_path, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open device");
        return;
    }
    write(fd, message, strlen(message));
    close(fd);
}

void record(int size) {
    int fd = open(device_path, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open device");
        return;
    }
    char *buffer = malloc(size);
    read(fd, buffer, size);
    printf("Recorded: ");
    for (int i = 0; i < size; i++) {
        printf("%hhx", buffer[i]);
    }
    printf("\n");
    free(buffer);
    close(fd);
}

int main() {
    int fd = open(device_path, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device");
        return 1;
    }

    set_volume(fd, 50);
    record(230);
    mute(fd);
    record(26);
    unmute(fd);
    record(442);

    set_volume(fd, 0);
    play("Testing playback at volume  0");

    set_volume(fd, 70);
    play("Playback at volume  70 sjdgjfhskjfiasjfijaijefijsdkjfkljpofppfdijpg[pgsdgjasdfljasfljsdfijsdfsdjisdagjsdajlajigjijsdidasgijdgsdgagdsaijgdsaihfsdopgasdijpgaigjsisdgjpgp[gjpdfijgdsopijgoipjijggijgghjfhigjgdsjasdglagsdkhggdasip]]");

    close(fd);
    return 0;
}
