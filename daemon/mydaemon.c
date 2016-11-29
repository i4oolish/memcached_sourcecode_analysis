// commit: haizhu.shao 2016-11-29 09:09
// mcp++实现更简单，直接调用系统api
int mydaemon(const char* name, int max_open_file_num) {
	daemon(1, 1);
	return initenv(name, max_open_file_num);
}

int initenv(const char* name, int max_open_file_num) {
	rlimit rlim;
	rlim.rlim_cur = max_open_file_num;
	rlim.rlim_max = max_open_file_num;
	int ret = setrlimit(RLIMIT_NOFILE, &rlim);
    if (ret != 0) {
        fprintf(stderr, "setrlimit to:%d error, errno:%d, msg:%m\n", max_open_file_num, errno);
    }

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigterm_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGCHLD, SIG_DFL);

	char tmp[128] = {0};
	sprintf(tmp, "%s.pid", name);
	FILE* pf = fopen(tmp, "w+");
	fprintf(pf, "%d\n", (int)getpid());
	fclose(pf);
  return ret;
}
