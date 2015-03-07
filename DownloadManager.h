#pragma once

void error(const char *err);

char *download_http(char *file_addr, char *host, int sockfd);