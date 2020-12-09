int makeEmptyFile(char *name)
{
	int f, cnt;
	char buf[BLOCK_SIZE];

	if (!name) {
		fprintf(stderr, "make_disk: invalid file name\n");
		return -1;
	}

	if ((f = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
		perror("make_disk: cannot open file");
		return -1;
	}

	memset(buf, 0, BLOCK_SIZE);
	for (cnt = 0; cnt < DISK_BLOCKS; ++cnt)
		write(f, buf, BLOCK_SIZE);

	close(f);

	return 0;
}