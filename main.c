#include <stdio.h>
#include <string.h>

int getbattery() {
	int ret = -1;
	FILE *fp = fopen("/sys/class/power_supply/BAT0/capacity", "r");
	if (!fp) {
		fprintf(stderr, "Could not open capacity file!\n");
		return -1;
	}
	fscanf(fp, "%d", &ret);
	fclose(fp);
	return ret;
}

const char *getstatus() {
	FILE *fp = fopen("/sys/class/power_supply/BAT0/status", "r");
	if (!fp) {
		fprintf(stderr, "Could not open status file!\n");
		return NULL;
	}
	char buf[128];
	memset(buf, 0, sizeof(buf));
	fread(buf, sizeof(char), sizeof(buf)-1, fp);
	fclose(fp);

	if (strcmp(buf,"Discharging\n") == 0) {
		return "-";
	} else if (strcmp(buf, "Charging\n") == 0) {
		return "+";
	} else if (strcmp(buf, "Full\n") == 0) {
		return "";
	}
	return "?";
}

int main() {
	int bat = getbattery();
	if (bat < 0) {
		fprintf(stderr, "Something whent wrong in battery check\n");
		return -1;
	}
	const char *status = getstatus();
	if (!status) {
		fprintf(stderr, "Something went wrong in status check\n");
		return -1;
	}
	printf("%s%d\n", status, bat);
	return 0;
}
