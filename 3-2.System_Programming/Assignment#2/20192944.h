#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <elf.h>

#define FIND_STR "software"

bool is_elf(Elf64_Ehdr eh);
void read_elf_header(int32_t fd, Elf64_Ehdr *elf_header);
void print_elf_header(Elf64_Ehdr elf_header);
char *read_section(int32_t fd, Elf64_Shdr sh);
void print_section_headers(int32_t fd, Elf64_Ehdr eh, Elf64_Shdr sh_table[]);
char *find_str(const char *target_str, const char *data, size_t size);

// Implement this function to check whether an input file is an elf file or not.
bool is_elf(Elf64_Ehdr elf_header)
{
	if (!strncmp((char *)elf_header.e_ident, "\177ELF", 4))
	{
		return true;
	}
	else
	{
		printf("It's not ELF file\n");
		return false;
	}
}

void read_elf_header(int32_t fd, Elf64_Ehdr *elf_header)
{
	assert(elf_header != NULL);
	assert(lseek(fd, (off_t)0, SEEK_SET) == (off_t)0);
	assert(read(fd, (void *)elf_header, sizeof(Elf64_Ehdr)) == sizeof(Elf64_Ehdr));
}

void print_elf_header(Elf64_Ehdr elf_header)
{
	printf("Storage class\t= ");
	switch (elf_header.e_ident[EI_CLASS])
	{
	case ELFCLASS32:
		printf("32-bit objects\n");
		break;

	case ELFCLASS64:
		printf("64-bit objects\n");
		break;

	default:
		printf("Unknwon CLASS\n");
		break;
	}

	printf("Data format\t= ");
	switch (elf_header.e_ident[EI_DATA])
	{
	case ELFDATA2LSB:
		printf("2's complement, little endian\n");
		break;

	case ELFDATA2MSB:
		printf("2's complement, big endian\n");
		break;

	default:
		printf("Unknwon Format\n");
		break;
	}

	printf("OS ABI\t\t= ");
	switch (elf_header.e_ident[EI_OSABI])
	{
	case ELFOSABI_SYSV:
		printf("UNIX System V ABI\n");
		break;

	case ELFOSABI_HPUX:
		printf("HP-UX\n");
		break;

	case ELFOSABI_NETBSD:
		printf("NetBSD\n");
		break;

	case ELFOSABI_LINUX:
		printf("Linux\n");
		break;

	case ELFOSABI_SOLARIS:
		printf("Sun Solaris\n");
		break;

	case ELFOSABI_AIX:
		printf("IBM AIX\n");
		break;

	case ELFOSABI_IRIX:
		printf("SGI Irix\n");
		break;

	case ELFOSABI_FREEBSD:
		printf("FreeBSD\n");
		break;

	case ELFOSABI_TRU64:
		printf("Compaq TRU64 UNIX\n");
		break;

	case ELFOSABI_MODESTO:
		printf("Novell Modesto\n");
		break;

	case ELFOSABI_OPENBSD:
		printf("OpenBSD\n");
		break;

	case ELFOSABI_ARM_AEABI:
		printf("ARM EABI\n");
		break;

	case ELFOSABI_ARM:
		printf("ARM\n");
		break;

	case ELFOSABI_STANDALONE:
		printf("Standalone (embedded) app\n");
		break;

	default:
		printf("Unknown (0x%x)\n", elf_header.e_ident[EI_OSABI]);
		break;
	}

	printf("Filetype \t= ");
	switch (elf_header.e_type)
	{
	case ET_NONE:
		printf("N/A (0x0)\n");
		break;

	case ET_REL:
		printf("Relocatable\n");
		break;

	case ET_EXEC:
		printf("Executable\n");
		break;

	case ET_DYN:
		printf("Shared Object\n");
		break;
	default:
		printf("Unknown (0x%x)\n", elf_header.e_type);
		break;
	}

	printf("Machine\t\t= ");
	switch (elf_header.e_machine)
	{
	case EM_NONE:
		printf("None (0x0)\n");
		break;

	case EM_386:
		printf("INTEL x86 (0x%x)\n", EM_386);
		break;

	case EM_X86_64:
		printf("AMD x86_64 (0x%x)\n", EM_X86_64);
		break;

	case EM_AARCH64:
		printf("AARCH64 (0x%x)\n", EM_AARCH64);
		break;

	default:
		printf(" 0x%x\n", elf_header.e_machine);
		break;
	}
	printf("\n");
}

char *read_section(int32_t fd, Elf64_Shdr sh)
{
	char *buff = malloc(sh.sh_size);
	if (!buff)
	{
		printf("%s:Failed to allocate %ldbytes\n",
			   __func__, sh.sh_size);
	}

	assert(buff != NULL);
	assert(lseek(fd, (off_t)sh.sh_offset, SEEK_SET) == (off_t)sh.sh_offset);
	assert(read(fd, (void *)buff, sh.sh_size) == sh.sh_size);

	return buff;
}

void print_section_headers(int32_t fd, Elf64_Ehdr eh, Elf64_Shdr sh_table[])
{
	uint32_t i;
	char *sh_str;

	assert(lseek(fd, (off_t)eh.e_shoff, SEEK_SET) == (off_t)eh.e_shoff);

	for (i = 0; i < eh.e_shnum; i++)
	{
		assert(read(fd, (void *)&sh_table[i], eh.e_shentsize) == eh.e_shentsize);
	}

	/* section-header string-table */
	sh_str = read_section(fd, sh_table[eh.e_shstrndx]);

	for (i = 0; i < eh.e_shnum; i++)
	{
		if (!strncmp((sh_str + sh_table[i].sh_name), ".rodata", 7))
		{
			printf("%s section info\n", (sh_str + sh_table[i].sh_name));
			printf("    file offset = 0x%08lx\n", sh_table[i].sh_offset);
			printf("           size = 0x%08lx\n", sh_table[i].sh_size);

			modify_rodata(fd, eh, sh_table);
		}
	}
}

void modify_rodata(int32_t fd, Elf64_Ehdr eh, Elf64_Shdr sh_table[])
{
	uint32_t i;
	char *sh_str;

	assert(lseek(fd, (off_t)eh.e_shoff, SEEK_SET) == (off_t)eh.e_shoff);

	for (i = 0; i < eh.e_shnum; i++)
	{
		assert(read(fd, (void *)&sh_table[i], eh.e_shentsize) == eh.e_shentsize);
	}

	/* section-header string-table */
	sh_str = read_section(fd, sh_table[eh.e_shstrndx]);
	for (i = 0; i < eh.e_shnum; i++)
	{
		if (!strncmp((sh_str + sh_table[i].sh_name), ".rodata", 7))
		{
			char *rodata_content = read_section(fd, sh_table[i]);

			// "software" 문자열 찾고, 주소값 반환
			char *found = find_str(FIND_STR, rodata_content, sh_table[i].sh_size);

			if (found)
			{
				off_t offset = sh_table[i].sh_offset + (found - rodata_content); // 오프셋 계산
				printf("[*] Found '%s' at offset %ld\n", FIND_STR, offset);

				// "software"를 "hackers!"로 변경
				const char *HACKERS = "hackers!";

				// 오프셋만큼 이동
				if (lseek(fd, offset, SEEK_SET) == -1)
				{
					perror("lseek failed");
					exit(EXIT_FAILURE);
				}

				// STDOUT
				ssize_t bytes_written = write(fd, HACKERS, sizeof(HACKERS));

				// 예외처리
				if (bytes_written == -1)
				{
					perror("write failed");
					exit(EXIT_FAILURE);
				}

				// 예외처리
				if (bytes_written == -1)
				{
					perror("pwrite failed");
					exit(EXIT_FAILURE);
				}
				printf("[*] Modify '%s' to 'hackers!'\n", FIND_STR);
			}
			else
			{
				printf("No '%s' found in this section.\n", FIND_STR);
			}
			// Deallocate memory
			free(rodata_content);
		}
	}
}

char *find_str(const char *target_str, const char *data, size_t size)
{
	size_t target_str_len = strlen(target_str);

	for (size_t i = 0; i < size; ++i)
	{
		if (data[i] == target_str[0]) // 첫 번째 문자 일치 확인
		{
			// 다음 문자들도 일치하는지 확인
			size_t j;
			for (j = 1; j < target_str_len; ++j)
			{
				if (data[i + j] != target_str[j])
					break;
			}
			if (j == target_str_len) // 모든 문자가 일치하면 발견한 것으로 간주
				return (char *)&data[i];
		}
	}

	return NULL; // 찾지 못한 경우
}
