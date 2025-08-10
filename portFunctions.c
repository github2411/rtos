void* memset(void *dst, int value, unsigned int size){
    unsigned char *ptr = (unsigned char *)dst;
    unsigned char byte_value = (unsigned char)value;

    //fill memory byte by byte
    while(size > 0){
        *ptr = byte_value;
        ptr++;
        size--;
    }
    return dst;  //return original pointer  as per standard
}
