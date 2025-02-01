#ifndef BUFFER_H
#define BUFFER_H

/**
 * Define a buffer structure with an array of string, size, direction ...
 */
typedef struct {
    /** a name to identify the struct. */
    const char* name;
    /** A type if name are equals. */
    const char* type;
    /** A pointer on an array of char. */
    unsigned char (*s)[];
    /** The max length of the buffer. */
    unsigned int length;
    /** The pointer used to write Data (we write at the end). */
    unsigned int writeIndex;
    /** The pointer used to read (we read at the begin). */
    unsigned int readIndex;
    /** the corresponding outputStream. */
    //OutputStream outputStream;
    /** the corresponding inputStream. */
    //InputStream inputStream;
} Buffer;


void writeBuffer(char* str);

char* readBuffer(void);

#endif