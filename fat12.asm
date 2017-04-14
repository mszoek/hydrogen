# Set memory segment that will receive the file:
mov     ax, loadsegment
mov     es, ax
# Set memory offset for loading to 0.
xor     bx, bx

# Set memory segment for FAT:
mov     cx, file_strt             # CX now points to first FAT entry of file

read_file_next_sector:
# Locate sector:
mov     ax, cx                    # Sector to read is equal to current FAT entry
add     ax, root_strt             # Plus the start of the root directory
add     ax, root_scts             # Plus the size of the root directory
sub     ax, 2                     # ... but minus 2

# Read sector:
push    cx                        # Read a sector from disk, but save CX
call    ReadSector                # as it contains our FAT entry
pop     cx
add     bx, iSectSize             # Move memory pointer to next section

# Get next sector from FAT:
push    ds                        # Make DS:SI point to FAT table
mov     dx, fatsegment            # in memory.
mov     ds, dx

mov     si, cx                    # Make SI point to the current FAT entry
mov     dx, cx                    # (offset is entry value * 1.5 bytes)
shr     dx
add     si, dx

mov     dx, ds:[si]               # Read the FAT entry from memory
test    cx, 1                     # See which way to shift, see if current cluster if odd
jnz     read_next_cluster_odd
and     dx, 0x0fff                # if not mask out upper 4 bits
jmp     read_next_file_cluster_done
read_next_cluster_odd:            # if it is odd shift the new cluster 4 to right
shr     dx, 4
read_next_file_cluster_done:
pop     ds                        # Restore DS to the normal data segment
mov     cx, dx                    # Store the new FAT entry in CX
cmp     cx, 0xff8                 # If the FAT entry is greater or equal
jl      read_file_next_sector     # to 0xff8, then we have reached end-of-file
