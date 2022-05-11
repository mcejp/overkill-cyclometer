## Data storage in Flash

- offset 256 * 1024 B
- erase sector size: 4096 B
- write page size: 256 B

Currently only one sector is used.

First page: header

```c
struct Flash_header {
    uint8_t magic[8];
    uint16_t version;
    uint16_t generation;
    uint16_t reserved_;
    uint16_t header_checksum;
    uint8_t pad[FLASH_WRITE_PAGE_SIZE - 16];
};
```

Following pages: data records

```c
struct Flash_record {
    uint32_t value;
    uint32_t value_checksum;
    uint8_t pad[FLASH_WRITE_PAGE_SIZE - 8];
};
```

Storage algorithm:

- format flash by erasing sector & writing header
- sequentially write record (latest record with valid checksum always prevails)
- when filled up, must reformat and start from scratch
