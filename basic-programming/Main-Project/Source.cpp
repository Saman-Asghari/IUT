#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>
#pragma warning(disable:4996)
void adminfirstpage(int day);
void monthly();
void addmariz();
void showvisit(int goal);
void printnoskhe(int goal);
void reservedvisits(int goal, int day);
void noskhenevisi(int goal, int day);
void marizfirstpage(int goal, int day);
void adddoctor();
void visits(int day);
void visirspay(int goal);
void extension(int goal);
void book(int goal, int day);
void cancel(int goal);
void payment(int goal);
void forgotpassword();
void determineshifts(int goal);
void loginpage(int day);
void pay(int goal);
void firstpage();
void doctorfirstpage(int goal, int day);
struct min {
	int flag;
	int min;
};
struct hour {
	int flag;
	int hour;
	struct min mins[2];
};
struct day {
	int day;
	int nameday;
	int flag;
	char toozih[40];
	struct hour helphour[13];
	struct hour hours[13];
};
struct month {
	char firstday[20];
	int daynumbers;
	char monthname[20];
	struct day days[31];
};
struct visits {
	month monthdoctor;
};
struct doctor {
	char email[40];
	char codemeli[40];
	char password[40];
	int days[7];
	int people[10];
	hour hours[10];
	int money = 0;
	int helping[4];
	int index;
	int monthcounter;
	int extracounter;
	int debth = 0;
	int twentypay;
	int visitprice;
	int marizindex[10];
	int mariznum = 0;
	int vojood = 1;
	struct month month;
};
struct visitmariz {
	char noskhe[100];
	struct day daysvisit;
	int flag;
	int doctorindex;
};
struct mariz {
	char email[40];
	char codemeli[40];
	char password[40];
	int money;
	int index;
	int savedoc[7];
	int visitnum = 0;
	struct visitmariz info[10];
};

int main() {
	FILE* fp;
	int test;
	int count = 0;
	//mariz* tests = (mariz*)malloc(sizeof(mariz) * 10);
	//fp = fopen("fdoctor.txt", "rb");
	//fread(tests, sizeof(mariz), 3, fp);
	//fclose(fp);
	//printf("%s %s", tests[0].codemeli, tests[1].codemeli);
	fp = fopen("fdoctor.txt", "rb");
	if (fp == NULL) {
		fp = fopen("fdoctor.txt", "wb");
		fclose(fp);
	}
	fp = fopen("fmariz.txt", "rb");
	if (fp == NULL) {
		fp = fopen("fmariz.txt", "wb");
		fclose(fp);
	}
	fp = fopen("fmarizcounter.txt", "rb");
	if (fp == NULL) {
		fp = fopen("fmarizcounter.txt", "wb");
		fclose(fp);
	}
	fp = fopen("fmonthcounter.txt", "rb");
	if (fp == NULL) {
		fp = fopen("fmonthcounter.txt", "wb");
		fclose(fp);
	}
	fp = fopen("fdoctorcounter.txt", "rb");
	if (fp == NULL) {
		fp = fopen("fdoctorcounter.txt", "wb");
		fclose(fp);
	}
	fp = fopen("fmonth.txt", "rb");
	if (fp == NULL) {
		fp = fopen("fmonth.txt", "wb");
		fclose(fp);
	}
	fp = fopen("fmarizcounter.txt", "rb");
	if (fread(&test, sizeof(int), 1, fp) == NULL) {
		fclose(fp);
		fp = fopen("fmarizcounter.txt", "wb");
		putw(count, fp);
		fclose(fp);
	}
	fp = fopen("fdoctorcounter.txt", "rb");
	if (fread(&test, sizeof(int), 1, fp) == NULL) {
		fclose(fp);
		fp = fopen("fdoctorcounter.txt", "wb");
		putw(count, fp);
		fclose(fp);
	}
	fp = fopen("fmonthcounter.txt", "rb");
	if (fread(&test, sizeof(int), 1, fp) == NULL) {
		fclose(fp);
		fp = fopen("fmonthcounter.txt", "wb");
		putw(count, fp);
		fclose(fp);
	}
	firstpage();

}
void visirspay(int goal) {
	FILE* fp;
	doctor temp[10];
	int doccount;
	int temping;
	fp = fopen("fdoctorcounter.txt", "rb");
	fread(&doccount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fdoctor.txt", "rb");
	fread(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
	while (1) {
		printf("enter the reservation price \n");
		scanf("%d", &temping);
		if (temping < 10 || temping>50) {
			system("cls");
		}
		else {

			break;
		}
	}
	fp = fopen("fdoctor.txt", "wb");
	fwrite(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
}
void book(int goal, int day) {
	system("cls");
	int holding;
	FILE* fp;
	int counter = 0;
	int doccount;
	int marizcount;
	int reserv;
	int choose;
	int helpdate;
	int help[20];
	int chert = 0;
	int nobat = 0;
	doctor temp[10];
	mariz temp2[40];
	month months;
	fp = fopen("fdoctorcounter.txt", "rb");
	fread(&doccount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fdoctor.txt", "rb");
	fread(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
	fp = fopen("fmarizcounter.txt", "rb");
	fread(&marizcount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fmariz.txt", "rb");
	fread(temp2, sizeof(mariz), marizcount, fp);
	fclose(fp);
	fp = fopen("fmonth.txt", "rb");
	fread(&months, sizeof(month), 1, fp);
	fclose(fp);
	printf("choose the doctor\n");
	for (int i = 0; i < doccount; i++) {
		if (temp[i].vojood == 1) {
			printf("%d.   %s\n", counter + 1, temp[i].codemeli);
			help[counter] = temp[i].index;
			counter++;
		}
	}
	scanf("%d", &choose);
	choose = help[choose - 1];
	if (temp[choose - 1].mariznum == 0) {
		for (int i = 0; i < months.daynumbers; i++) {
			for (int j = 0; j < 13; j++) {
				for (int z = 0; z < 2; z++) {
					if (z % 2 == 0) {
						temp[choose - 1].month.days[i].hours[j].mins[z].min = 0;
						temp[choose - 1].month.days[i].hours[j].mins[z].flag = 1;
						temp[choose - 1].month.days[i].helphour[j].flag = 1;
					}
					else {
						temp[choose - 1].month.days[i].hours[j].mins[z].min = 30;
						temp[choose - 1].month.days[i].hours[j].mins[z].flag = 1;
						temp[choose - 1].month.days[i].helphour[j].flag = 1;
					}
				}
			}
		}
	}
	nobat = 0;
	helpdate = (day + months.days[0].nameday - 1) % 7;
	holding = day;
	system("cls");
	for (int i = helpdate; i < 6; i++) {
		printf("%d\n", months.days[day - 1].day);
		if (temp[choose - 1].month.days[day - 1].flag == 1) {
			for (int m = 0; m < 13; m++) {
				if (temp[choose - 1].month.days[day - 1].hours[m].flag == 1)
					chert++;
			}
			for (int j = 0; j < chert - 1; j++) {
				for (int x = 0; x < 2; x++) {
					if (x % 2 == 0) {
						if (temp[choose - 1].month.days[day - 1].hours[j].mins[x].flag == 1) {
							printf("%d.%d:%d  ta  %d:%d\n", nobat, temp[choose - 1].month.days[day - 1].hours[j].hour, temp[choose - 1].month.days[day - 1].hours[j].mins[x].min, temp[choose - 1].month.days[day - 1].hours[j].hour, 30);
							nobat++;
						}
					}
					else {
						if (temp[choose - 1].month.days[day - 1].helphour[j + 1].flag == 1) {
							printf("%d.%d:%d  ta  %d:%d\n", nobat, temp[choose - 1].month.days[day - 1].hours[j].hour, temp[choose - 1].month.days[day - 1].hours[j].mins[x].min, temp[choose - 1].month.days[day - 1].hours[j + 1].hour, 00);
							nobat++;
						}
					}
				}
			}
		}
		printf("\n-----------------------------------------------------------------------\n");
		day++;
		chert = 0;
	}
	day = holding;
	nobat = 1;
	scanf("%d", &reserv);
	reserv++;
	for (int i = helpdate; i < 6; i++) {
		printf("%d", months.days[day - 1].day);
		if (temp[choose - 1].month.days[day - 1].flag == 1) {
			for (int m = 0; m < 13; m++) {
				if (temp[choose - 1].month.days[day - 1].hours[m].flag == 1)
					chert++;
			}
			for (int j = 0; j < chert - 1; j++) {
				for (int x = 0; x < 2; x++) {
					if (x % 2 == 0) {
						if (temp[choose - 1].month.days[day - 1].hours[j].mins[x].flag == 1) {
							if (reserv == nobat) {
								temp2[goal].info[temp2[goal].visitnum].flag = 1;
								temp2[goal].info[temp2[goal].visitnum].daysvisit.hours[0].mins[0] = temp[choose - 1].month.days[day - 1].hours[j].mins[x];
								temp2[goal].info[temp2[goal].visitnum].daysvisit.day = months.days[day - 1].day;
								temp2[goal].info[temp2[goal].visitnum].daysvisit.hours[0].hour = temp[choose - 1].month.days[day - 1].hours[j].hour;
								temp2[goal].info[temp2[goal].visitnum].doctorindex = temp[choose - 1].index - 1;
								temp[choose - 1].marizindex[temp[choose - 1].mariznum] = goal;
								temp[choose - 1].mariznum++;
								temp2[goal].visitnum++;
								temp2[goal].money = temp2[goal].money - 1.1 * (temp[choose - 1].visitprice);
								temp[choose - 1].month.days[day - 1].hours[j].mins[x].flag = 0;
							}
							nobat++;
						}
					}

					else {
						if (temp[choose - 1].month.days[day - 1].helphour[j + 1].flag == 1) {
							if (reserv == nobat) {
								temp2[goal].info[temp2[goal].visitnum].flag = 1;
								temp2[goal].info[temp2[goal].visitnum].daysvisit.hours[0].mins[0] = temp[choose - 1].month.days[day - 1].hours[j].mins[x];
								temp2[goal].info[temp2[goal].visitnum].daysvisit.day = months.days[day - 1].day;
								temp2[goal].info[temp2[goal].visitnum].daysvisit.hours[0].hour = temp[choose - 1].month.days[day - 1].hours[j].hour;
								temp2[goal].info[temp2[goal].visitnum].doctorindex = temp[choose - 1].index - 1;
								temp[choose - 1].marizindex[temp[choose - 1].mariznum] = goal;
								temp[choose - 1].mariznum++;
								temp2[goal].visitnum++;
								temp2[goal].money = temp2[goal].money - 1.1 * (temp[choose - 1].visitprice);
								temp[choose - 1].month.days[day - 1].helphour[j + 1].flag = 0;
							}
							nobat++;
						}
					}
				}
			}
		}
		day++;
		chert = 0;
	}
	fp = fopen("fdoctor.txt", "wb");
	fwrite(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
	fp = fopen("fmariz.txt", "wb");
	fwrite(temp2, sizeof(mariz), marizcount, fp);
	fclose(fp);
}
void reservedvisits(int goal, int day) {
	int doccount;
	int help = 0;
	int marizcount;
	FILE* fp;
	int helpday;
	mariz temp2[40];
	doctor temp[10];
	month months;
	fp = fopen("fdoctorcounter.txt", "rb");
	fread(&doccount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fdoctor.txt", "rb");
	fread(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
	fp = fopen("fmarizcounter.txt", "rb");
	fread(&marizcount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fmariz.txt", "rb");
	fread(temp2, sizeof(mariz), marizcount, fp);
	fclose(fp);
	fp = fopen("fmonth.txt", "rb");
	fread(&months, sizeof(month), 1, fp);
	fclose(fp);
	system("cls");
	helpday = (day + months.days[0].nameday - 1) % 7;
	for (int i = helpday; i < 6; i++) {
		if (temp[goal].month.days[day].flag == 1) {
			for (int m = 0; m < 40; m++) {
				for (int z = 0; z < 10; z++) {
					if (temp2[m].info[z].doctorindex == goal && temp2[m].info[z].daysvisit.day == (day + 1) && temp2[m].info[z].flag == 1) {
						printf("%d.%d:", temp2[m].info[z].daysvisit.day, temp2[m].info[z].daysvisit.hours[0].hour);
						if (temp2[m].info[z].daysvisit.hours[0].mins[0].min == 0) {
							printf("%d  ta  %d:30", temp2[m].info[z].daysvisit.hours[0].mins[0].min, temp2[m].info[z].daysvisit.hours[0].hour);
						}
						else {
							printf("%d  ta  %d:00", temp2[m].info[z].daysvisit.hours[0].mins[0].min, temp2[m].info[z].daysvisit.hours[0].hour + 1);

							printf("             mariz id:%d    mariz username:%s   mariz email:%s\n", temp2[m].index - 1, temp2[m].codemeli, temp2[m].email);

						}
					}
				}
			}

		}
		day++;
		printf("----------------------------------------------------------");
	}
	_sleep(5000);

}
void determineshifts(int goal) {
	FILE* fp;
	int counter;
	int action;
	int doccount;
	int note[40];
	int notecounter = 0;
	int helping;
	int count;
	int tempday[20];
	int temphour[20];
	int tempend[20];
	doctor temp[10];
	struct month temp2;
	fp = fopen("fdoctorcounter.txt", "rb");
	fread(&doccount, sizeof(int), 1, fp);
	fclose(fp);
	printf("1.set for day\n2.Recurring days in the month\n");
	scanf("%d", &action);
	fp = fopen("fdoctor.txt", "rb");
	fread(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
	fp = fopen("fmonth.txt", "rb");
	fread(&temp2, sizeof(month), 1, fp);
	fclose(fp);
	if (action == 1) {
		printf("enter the number of days u want to come\n");
		scanf("%d", &count);
		printf("now enter the day and the hour of the begining and end\n");
		for (int i = 0; i < count; i++) {
			scanf("%d", &tempday[i]);
			scanf("%d", &temphour[i]);
			scanf("%d", &tempend[i]);
			temp[goal].month.days[tempday[i] - 1].day = tempday[i];
			if (((tempday[i] + temp2.days[0].nameday - 1) % 7) == 6) {
				printf("clinick is closed\n");
				i--;
			}
			else {
				if (((tempday[i] + temp2.days[0].nameday - 1) % 7) == 5) {
					if (temphour[i] < 8 || tempend[i]>13) {
						printf("clinick is closed\n");
					}
					i--;
				}
				else {
					if (temphour[i] < 8 || tempend[i]>21) {
						printf("clinick is closed");
						i--;
					}
				}
			}
		}
		for (int i = 0; i < count; i++) {
			temp[goal].month.days[tempday[i] - 1].day = tempday[i];
			if (temp2.days[tempday[i] - 1].flag == 0) {
				temp[goal].month.days[tempday[i] - 1].flag = 1;
				for (int j = 0; j <= tempend[i] - temphour[i]; j++) {
					temp[goal].month.days[tempday[i] - 1].hours[j].flag = 1;
					temp[goal].month.days[tempday[i] - 1].hours[j].hour = temphour[i] + j;
				}
			}
			else {
				note[notecounter] = temp2.days[tempday[i] - 1].day;
				notecounter++;
			}
		}
		if (notecounter != 0) {
			printf("Note!the day that clinick is closed!!");
			for (int i = 0; i < notecounter; i++) {
				printf("%d ", note[i]);
			}
		}

	}
	if (action == 2) {
		printf("how many days you want to come in a week");
		scanf("%d", &counter);
		for (int i = 0; i < counter; i++) {
			scanf("%d", &temp[goal].days[i]);
			scanf("%d", &temp[goal].hours[i].hour);
			scanf("%d", &temp[goal].helping[i]);
			if (temp[goal].days[i] == 6) {
				printf("clinick is not availlible!!\n");
				i--;
			}
			else {
				if (temp[goal].days[i] == 5) {
					if (temp[goal].hours[0].hour < 8 || temp[goal].helping[i]>13) {
						printf("clinick is not availlible!!\n");
						i--;
					}
				}
				else {
					if (temp[goal].hours[0].hour < 8 || temp[goal].helping[i]>21) {
						printf("clinick is not availlible!!\n");
						i--;
					}

				}

			}
		}
		for (int i = 0; i < counter; i++) {
			for (int j = 0; j < temp2.daynumbers; j++) {
				if (temp2.days[j].nameday == temp[goal].days[i]) {
					if (temp2.days[j].flag == 0) {
						temp[goal].month.days[j].flag = 1;
						for (int m = 0; m <= temp[goal].helping[i] - temp[goal].hours[i].hour; m++) {
							temp[goal].month.days[j].hours[m].flag = 1;
							temp[goal].month.days[j].hours[m].hour = temp[goal].hours[i].hour + m;
						}
					}
					else {
						note[notecounter] = temp2.days[j].day;
						notecounter++;
					}
				}
			}
		}
		if (notecounter != 0) {
			printf("Note!the day that clinick is closed!!");
			for (int i = 0; i < notecounter; i++) {
				printf("%d ", note[i]);
			}
		}
	}

	fp = fopen("fdoctor.txt", "wb");
	fwrite(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
	_sleep(5000);
}
void cancel(int goal) {
	int doccount;
	int help = 0;
	int marizcount;
	int choice;
	char trash[3];
	FILE* fp;
	int helpday;
	mariz temp2[40];
	doctor temp[10];
	month months;
	int day;
	int helping = 0;
	int counter = 1;
	int marizcounter;
	fp = fopen("fdoctorcounter.txt", "rb");
	fread(&doccount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fdoctor.txt", "rb");
	fread(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
	fp = fopen("fmarizcounter.txt", "rb");
	fread(&marizcount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fmariz.txt", "rb");
	fread(temp2, sizeof(mariz), marizcount, fp);
	fclose(fp);
	fp = fopen("fmonth.txt", "rb");
	fread(&months, sizeof(month), 1, fp);
	fclose(fp);
	system("cls");
	for (int i = 0; i < temp2[goal].visitnum; i++) {
		if (temp2[goal].info[i].flag == 1) {
			printf("%d.day:%d  ", i + 1, temp2[goal].info[i].daysvisit.day);
			printf("time: %d:%d   ta    ", temp2[goal].info[i].daysvisit.hours[0].hour, temp2[goal].info[i].daysvisit.hours[0].mins[0].min);
			if (temp2[goal].info[i].daysvisit.hours[0].mins[0].min == 0) {
				printf("%d:30\n", temp2[goal].info[i].daysvisit.hours[0].hour);
			}
			else {
				printf("%d:00\n", temp2[goal].info[i].daysvisit.hours[0].hour + 1);
			}
		}
	}
	scanf("%d", &choice);
	choice--;
	temp2[goal].info[choice].flag = 0;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 2; j++) {
			if (temp[temp2[goal].info[choice].doctorindex].month.days[temp2[goal].info[choice].daysvisit.day - 1].hours[i].mins[j].min == temp2[goal].info[choice].daysvisit.hours[0].mins[0].min && temp[temp2[goal].info[choice].doctorindex].month.days[temp2[goal].info[choice].daysvisit.day - 1].hours[i].hour == temp2[goal].info[choice].daysvisit.hours[0].hour) {
				temp[temp2[goal].info[choice].doctorindex].month.days[temp2[goal].info[choice].daysvisit.day - 1].helphour[i - 1].flag = 1;
				temp[temp2[goal].info[choice].doctorindex].month.days[temp2[goal].info[choice].daysvisit.day - 1].hours[i].mins[j].flag = 1;
			}

		}
	}
	fp = fopen("fdoctor.txt", "wb");
	fwrite(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
	fp = fopen("fmariz.txt", "wb");
	fwrite(temp2, sizeof(mariz), marizcount, fp);
	fclose(fp);
}
void showvisit(int goal) {
	int doccount;
	int help = 0;
	int marizcount;
	int choice;
	char trash[3];
	FILE* fp;
	int helpday;
	mariz temp2[40];
	doctor temp[10];
	month months;
	int day;
	int helping = 0;
	int counter = 1;
	int marizcounter;
	fp = fopen("fdoctorcounter.txt", "rb");
	fread(&doccount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fdoctor.txt", "rb");
	fread(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
	fp = fopen("fmarizcounter.txt", "rb");
	fread(&marizcount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fmariz.txt", "rb");
	fread(temp2, sizeof(mariz), marizcount, fp);
	fclose(fp);
	fp = fopen("fmonth.txt", "rb");
	fread(&months, sizeof(month), 1, fp);
	fclose(fp);
	system("cls");
	for (int i = 0; i < temp2[goal].visitnum; i++) {
		if (temp2[goal].info[i].flag == 1) {
			printf("%d.day:%d  ", i + 1, temp2[goal].info[i].daysvisit.day);
			printf("time: %d:%d   ta    ", temp2[goal].info[i].daysvisit.hours[0].hour, temp2[goal].info[i].daysvisit.hours[0].mins[0].min);
			if (temp2[goal].info[i].daysvisit.hours[0].mins[0].min == 0) {
				printf("%d:30\n", temp2[goal].info[i].daysvisit.hours[0].hour);
			}
			else {
				printf("%d:00\n", temp2[goal].info[i].daysvisit.hours[0].hour + 1);
			}
		}
	}
	_sleep(5000);
}
void noskhenevisi(int goal, int day) {
	int doccount;
	int help = 0;
	int marizcount;
	int choice;
	char trash[3];
	FILE* fp;
	int helpday;
	mariz temp2[40];
	doctor temp[10];
	month months;
	int helping;
	int counter = 1;
	int marizcounter;
	fp = fopen("fdoctorcounter.txt", "rb");
	fread(&doccount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fdoctor.txt", "rb");
	fread(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
	fp = fopen("fmarizcounter.txt", "rb");
	fread(&marizcount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fmariz.txt", "rb");
	fread(temp2, sizeof(mariz), marizcount, fp);
	fclose(fp);
	fp = fopen("fmonth.txt", "rb");
	fread(&months, sizeof(month), 1, fp);
	fclose(fp);
	system("cls");
	helping = day;
	helpday = (day + months.days[0].nameday - 1) % 7;
	for (int i = helpday; i < 6; i++) {
		if (temp[goal].month.days[day].flag == 1) {
			for (int m = 0; m < 40; m++) {
				for (int z = 0; z < 10; z++) {
					if (temp2[m].info[z].doctorindex == goal && temp2[m].info[z].daysvisit.day == (day + 1) && temp2[m].info[z].flag == 1) {
						printf("%d.%d\n", counter, temp2[m].index);
						printf("-------------------------------------\n");
						counter++;
					}
				}
			}

		}
		day++;
	}
	day = helping;
	counter = 0;
	scanf("%d", &choice);
	gets_s(trash);
	for (int i = helpday; i < 6; i++) {
		if (temp[goal].month.days[day].flag == 1) {
			for (int m = 0; m < 40; m++) {
				for (int z = 0; z < 10; z++) {
					if (temp2[m].info[z].doctorindex == goal && temp2[m].info[z].daysvisit.day == (day + 1) && temp2[m].info[z].flag == 1) {
						counter++;
						if (choice == counter) {
							gets_s(temp2[m].info[z].noskhe);
						}
					}
				}
			}

		}
		day++;
	}
	temp[goal].money = temp[goal].money + temp[goal].visitprice;
	fp = fopen("fmariz.txt", "wb");
	fwrite(temp2, sizeof(mariz), marizcount, fp);
	fclose(fp);
	fp = fopen("fdoctor.txt", "wb");
	fwrite(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
}
void extension(int goal) {
	int doccount;
	int help = 0;
	int marizcount;
	int choice;
	char trash[3];
	FILE* fp;
	int helpday;
	doctor temp[10];
	month months;
	int day;
	int helping;
	int counter = 1;
	int marizcounter;
	fp = fopen("fdoctorcounter.txt", "rb");
	fread(&doccount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fdoctor.txt", "rb");
	fread(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
	fp = fopen("fmonth.txt", "rb");
	fread(&months, sizeof(month), 1, fp);
	fclose(fp);
	system("cls");
	if (temp[goal].twentypay == 0) {
		temp[goal].twentypay = 2;
		temp[goal].debth = 1;
	}
	else {
		printf("you cant use this option now!!");
	}
	fp = fopen("fdoctor.txt", "wb");
	fwrite(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
}
void payment(int goal) {
	int doccount;
	int help = 0;
	int marizcount;
	int choice;
	char trash[3];
	FILE* fp;
	int helpday;
	doctor temp[10];
	month months;
	int day;
	int helping;
	int counter = 1;
	int marizcounter;
	fp = fopen("fdoctorcounter.txt", "rb");
	fread(&doccount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fdoctor.txt", "rb");
	fread(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
	fp = fopen("fmonth.txt", "rb");
	fread(&months, sizeof(month), 1, fp);
	fclose(fp);
	system("cls");
	if (temp[goal].twentypay == 2) {
		if (temp[goal].money < months.daynumbers * 20) {
			printf("you dont have enough money");
			temp[goal].debth++;
			if (temp[goal].debth >= 2) {
				temp[goal].vojood = 0;
			}
		}
		else {
			temp[goal].money = temp[goal].money - (months.daynumbers * 20);
			temp[goal].debth = 0;
		}
	}
	else {
		if (temp[goal].money < months.daynumbers * 10) {
			printf("you dont have enough money");
			temp[goal].debth++;
			if (temp[goal].debth >= 2) {
				temp[goal].vojood = 0;
			}
		}
		else {
			temp[goal].debth = 0;
			temp[goal].money = temp[goal].money - (months.daynumbers * 10);
			if (temp[goal].twentypay != 0) {
				temp[goal].twentypay = temp[goal].twentypay - 1;
			}
		}
	}
	fp = fopen("fdoctor.txt", "wb");
	fwrite(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
}
void pay(int goal) {
	int doccount;
	int help = 0;
	int marizcount;
	int choice;
	char trash[3];
	FILE* fp;
	int helpday;
	doctor temp[10];
	month months;
	int day;
	int helping;
	int counter = 1;
	int marizcounter;
	fp = fopen("fdoctorcounter.txt", "rb");
	fread(&doccount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fdoctor.txt", "rb");
	fread(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
	fp = fopen("fmonth.txt", "rb");
	fread(&months, sizeof(month), 1, fp);
	fclose(fp);
	system("cls");
	printf("1.extension\n2.payment");
	printf("choose your option");
	scanf("%d", &choice);
	if (choice == 1) {
		extension(goal);
	}
	if (choice == 2) {
		payment(goal);
	}

}
void printnoskhe(int goal) {
	int doccount;
	int help = 0;
	int marizcount;
	int choice;
	char trash[3];
	FILE* fp;
	int helpday;
	mariz temp2[40];
	doctor temp[10];
	month months;
	int day;
	int helping;
	int counter = 1;
	int marizcounter;
	fp = fopen("fdoctorcounter.txt", "rb");
	fread(&doccount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fdoctor.txt", "rb");
	fread(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
	fp = fopen("fmarizcounter.txt", "rb");
	fread(&marizcount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fmariz.txt", "rb");
	fread(temp2, sizeof(mariz), marizcount, fp);
	fclose(fp);
	fp = fopen("fmonth.txt", "rb");
	fread(&months, sizeof(month), 1, fp);
	fclose(fp);
	system("cls");
	for (int i = 0; i < temp2[goal].visitnum; i++) {
		if (temp2[goal].info[i].flag == 1) {
			if (temp2[goal].info[i].noskhe[0] != -51) {
				printf("%d\n", temp2[goal].info[i].daysvisit.day);
				printf("doctor:%d   ", temp2[goal].info[i].doctorindex);
				printf("%s\n", temp2[goal].info[i].noskhe);
				printf("-------------------------------------------------\n");
			}
		}
	}
	_sleep(5000);
}
void doctorfirstpage(int goal, int day) {
	char trash[1];
	int action;
	while (1) {
		system("cls");
		printf("1.Determining the shifts\n2.Reserved Visits\n3.Patient Prescription\n4.Rent Payment\n5.Visirs Payment\n6.Exit");
		scanf("%d", &action);
		if (action == 1)
			determineshifts(goal);
		if (action == 2)
			reservedvisits(goal, day);
		if (action == 3)
			noskhenevisi(goal, day);
		if (action == 4)
			pay(goal);
		if (action == 5)
			visirspay(goal);
		if (action == 6)
			break;
	}
}
void marizfirstpage(int goal, int day) {
	int action;
	while (1) {
		system("cls");
		printf("1.Book an Appointment\n2.Cancel an Appointment\n3.All Appointments\n4.Prescriptions\n5.Exit\n");
		scanf("%d", &action);
		if (action == 1)
			book(goal, day);
		if (action == 2)
			cancel(goal);
		if (action == 3)
			showvisit(goal);
		if (action == 4)
			printnoskhe(goal);
		if (action == 5)
			break;
	}

}
void monthly() {
	mariz temp2[40];
	month months;
	int day;
	int helping;
	int counter = 1;
	int marizcount;
	FILE* fp;
	fp = fopen("fmarizcounter.txt", "rb");
	fread(&marizcount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fmariz.txt", "rb");
	fread(temp2, sizeof(mariz), marizcount, fp);
	fclose(fp);
	int action;
	int x;
	int holidays;
	char garbage[10];
	printf("enter the name of the month,number of days and first day in order:\n");
	scanf("%s %d %s", months.monthname, &months.daynumbers, months.firstday);
	system("cls");
	printf("if there is a holiday and you want to submit,enter 1 else enter 0:");
	scanf("%d", &action);
	if (action == 0) {

	}
	else {
		system("cls");
		printf("enter they days that are holiday and put a reson until -1\n");
		while (1) {
			scanf("%d", &holidays);
			if (holidays == -1)
				break;

			gets_s(months.days[holidays - 1].toozih);
			months.days[holidays - 1].flag = 1;
		}
	}
	for (int i = 0; i < months.daynumbers; i++) {
		if (months.days[i].flag == 1)
			continue;
		else {
			months.days[i].flag = 0;
		}

	}
	if (strcmp(months.firstday, "shanbe") == 0) {
		x = 0;
	}
	if (strcmp(months.firstday, "yekshanbe") == 0) {
		x = 1;
	}
	if (strcmp(months.firstday, "doshanbe") == 0) {
		x = 2;
	}
	if (strcmp(months.firstday, "seshanbe") == 0) {
		x = 3;
	}
	if (strcmp(months.firstday, "charshanbe") == 0) {
		x = 4;
	}
	if (strcmp(months.firstday, "panjshanbe") == 0) {
		x = 5;
	}
	if (strcmp(months.firstday, "jomeh") == 0) {
		x = 6;
	}
	for (int i = 1; i <= months.daynumbers; i++) {
		months.days[i - 1].day = i;
		months.days[i - 1].nameday = (x + i - 1) % 7;
	}

	printf("\n0 1 2 3 4 5 6 \n");
	for (int i = 0; i < x; i++) {
		printf("  ");
	}
	for (int i = 0; i < months.daynumbers; i++) {
		printf("%d ", i + 1);
		if (months.days[i].nameday == 6)
			printf("\n");
	}
	printf("\n");
	for (int i = 0; i < months.daynumbers; i++) {
		if (months.days[i].flag == 1) {
			printf("%d.%s\n", i + 1, months.days[i].toozih);
		}
	}
	for (int i = 0; i < marizcount; i++) {
		for (int j = 0; j < 10; j++) {
			temp2[i].info[j].flag = 0;
		}
	}
	fp = fopen("fmariz.txt", "wb");
	fwrite(temp2, sizeof(mariz), marizcount, fp);;
	fclose(fp);
	fp = fopen("fmonth.txt", "wb");
	fwrite(&months, sizeof(months), 1, fp);
	fclose(fp);
	system("cls");
}
void addmariz() {
	FILE* fp;
	int id;
	mariz help;
	fp = fopen("fmarizcounter.txt", "rb");
	fread(&id, sizeof(int), 1, fp);
	fclose(fp);
	system("cls");
	printf("enter the mariz code meli ,password email and money\n");
	scanf("%s %s %s %d", help.codemeli, help.password, help.email, &help.money);
	help.index = id + 1;
	fp = fopen("fmarizcounter.txt", "wb");
	int id2 = id + 1;
	putw(id2, fp);
	fclose(fp);
	fp = fopen("fmariz.txt", "ab");
	fwrite(&help, sizeof(mariz), 1, fp);
	fclose(fp);
}
void adddoctor() {
	system("cls");
	int id;
	int x = 0;
	doctor temp[10];
	doctor help;
	FILE* fp;
	fp = fopen("fdoctorcounter.txt", "rb");
	fread(&id, sizeof(int), 1, fp);
	fclose(fp);
	printf("enter the doctor code meli,password and email:\n");
	scanf("%s %s %s", help.codemeli, help.password, help.email);
	if (id != 0) {
		fp = fopen("fdoctor.txt", "rb");
		fread(temp, sizeof(doctor), id, fp);
		for (int i = 0; i < id; i++) {
			if (strcmp(help.codemeli, temp[i].codemeli) == 0) {
				printf("doctor exists!!\n");
				x = 1;
				break;
			}
		}

	}
	fclose(fp);
	if (x == 0) {
		help.index = id + 1;
		help.money = 10;
		int id2 = id + 1;
		fp = fopen("fdoctorcounter.txt", "wb");
		putw(id2, fp);
		fclose(fp);
		fp = fopen("fdoctor.txt", "ab");
		fwrite(&help, sizeof(doctor), 1, fp);
		fclose(fp);
	}
}
void visits(int day) {
	int doccount;
	int help = 0;
	int marizcount;
	int choice;
	int arr[10];
	int choose;
	char trash[3];
	FILE* fp;
	int counting = 0;
	int helpday;
	mariz temp2[40];
	doctor temp[10];
	month months;
	int helping;
	int counter = 1;
	int marizcounter;
	fp = fopen("fdoctorcounter.txt", "rb");
	fread(&doccount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fdoctor.txt", "rb");
	fread(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
	fp = fopen("fmarizcounter.txt", "rb");
	fread(&marizcount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fmariz.txt", "rb");
	fread(temp2, sizeof(mariz), marizcount, fp);
	fclose(fp);
	fp = fopen("fmonth.txt", "rb");
	fread(&months, sizeof(month), 1, fp);
	fclose(fp);
	system("cls");
	printf("1.all\n2.choose doctor\n");
	scanf("%d", &choice);
	helping = day;
	helpday = (day + months.days[0].nameday - 1) % 7;
	if (choice == 1) {
		for (int x = 0; x < doccount; x++) {
			if (temp[x].vojood == 1) {
				printf("%s", temp[x].codemeli);
				for (int i = helpday; i < 6; i++) {
					if (temp[x].month.days[day].flag == 1) {
						for (int m = 0; m < 40; m++) {
							for (int z = 0; z < 10; z++) {
								if (temp2[m].info[z].doctorindex == x && temp2[m].info[z].daysvisit.day == (day + 1) && temp2[m].info[z].flag == 1) {
									printf("%d.%d:", temp2[m].info[z].daysvisit.day, temp2[m].info[z].daysvisit.hours[0].hour);
									if (temp2[m].info[z].daysvisit.hours[0].mins[0].min == 0) {
										printf("%d  ta  %d:30", temp2[m].info[z].daysvisit.hours[0].mins[0].min, temp2[m].info[z].daysvisit.hours[0].hour);
										printf("             mariz id:%d    mariz username:%s   mariz email:%s\n", temp2[m].index - 1, temp2[m].codemeli, temp2[m].email);
										printf("----------------------------------------------------------\n");
									}
									else {
										printf("%d  ta  %d:00", temp2[m].info[z].daysvisit.hours[0].mins[0].min, temp2[m].info[z].daysvisit.hours[0].hour + 1);

										printf("             mariz id:%d    mariz username:%s   mariz email:%s\n", temp2[m].index - 1, temp2[m].codemeli, temp2[m].email);
										printf("----------------------------------------------------------\n");
									}
								}
							}
						}

					}
					day++;
				}
			}
			printf("**********************************************************\n");
			day = helping;
		}
	}
	if (choice == 2) {
		for (int i = 0; i < doccount; i++) {
			if (temp[i].vojood == 1) {
				printf("%d.   %s\n", counting + 1, temp[i].codemeli);
				arr[counting] = temp[i].index;
				counting++;
			}
		}
		scanf("%d", &choose);
		choose = arr[choose - 1];
		for (int i = helpday; i < 6; i++) {
			if (temp[choose - 1].month.days[day].flag == 1) {
				for (int m = 0; m < 40; m++) {
					for (int z = 0; z < 10; z++) {
						if (temp2[m].info[z].doctorindex == choose - 1 && temp2[m].info[z].daysvisit.day == (day + 1) && temp2[m].info[z].flag == 1) {
							printf("%d.%d:", temp2[m].info[z].daysvisit.day, temp2[m].info[z].daysvisit.hours[0].hour);
							if (temp2[m].info[z].daysvisit.hours[0].mins[0].min == 0) {
								printf("%d  ta  %d:30", temp2[m].info[z].daysvisit.hours[0].mins[0].min, temp2[m].info[z].daysvisit.hours[0].hour);
								printf("             mariz id:%d    mariz username:%s   mariz email:%s\n", temp2[m].index - 1, temp2[m].codemeli, temp2[m].email);
								printf("----------------------------------------------------------\n");
							}
							else {
								printf("%d  ta  %d:00", temp2[m].info[z].daysvisit.hours[0].mins[0].min, temp2[m].info[z].daysvisit.hours[0].hour + 1);

								printf("             mariz id:%d    mariz username:%s   mariz email:%s\n", temp2[m].index - 1, temp2[m].codemeli, temp2[m].email);
								printf("----------------------------------------------------------\n");

							}
						}
					}
				}

			}
			day++;
		}
	}
	_sleep(5000);
}
void adminfirstpage(int day) {
	int action;
	while (1) {
		system("cls");
		printf("\n1.add doctor\n2.add mariz\n3.monthly schedule\n4.visits schedule\n5.exit\n");
		printf("enter the action you want:");
		scanf("%d", &action);

		if (action == 1) {
			adddoctor();
		}
		if (action == 2) {
			addmariz();
		}
		if (action == 3) {
			monthly();
		}
		if (action == 4) {
			visits(day);
		}
		if (action == 5) {
			break;
		}
	}
}
void forgotpassword() {
	doctor temp[10];
	mariz temp2[40];
	system("cls");
	FILE* fp;
	int marizcount;
	int counter = 0;
	int doccount;
	char codemeli[20];
	char email[20];
	char newpassword[20];
	char trash[1];
	fp = fopen("fmarizcounter.txt", "rb");
	fread(&marizcount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fdoctorcounter.txt", "rb");
	fread(&doccount, sizeof(int), 1, fp);
	fclose(fp);
	gets_s(trash);
	printf("enter the username:");
	gets_s(codemeli);
	printf("\n");
	printf("enter the email:");
	gets_s(email);
	fp = fopen("fmariz.txt", "rb");
	fread(temp2, sizeof(mariz), marizcount, fp);
	fclose(fp);
	for (int i = 0; i < marizcount; i++) {
		if (strcmp(temp2[i].codemeli, codemeli) == 0) {
			if (strcmp(temp2[i].email, email) == 0) {
				system("cls");
				printf("enter new password:");
				gets_s(newpassword);
				strcpy(temp2[i].password, newpassword);
				fp = fopen("fmariz.txt", "wb");
				fwrite(temp2, sizeof(mariz), marizcount, fp);
				fclose(fp);
				counter++;
				break;
			}
		}
	}
	fp = fopen("fdoctor.txt", "rb");
	fread(temp, sizeof(doctor), doccount, fp);
	fclose(fp);
	for (int i = 0; i < marizcount; i++) {
		if (strcmp(temp[i].codemeli, codemeli) == 0) {
			if (strcmp(temp[i].email, email) == 0) {
				system("cls");
				printf("enter new password:");
				gets_s(newpassword);
				strcpy(temp[i].password, newpassword);
				fp = fopen("fdoctor.txt", "wb");
				fwrite(temp, sizeof(doctor), doccount, fp);
				fclose(fp);
				counter++;
				break;
			}
		}
	}
	if (counter == 0) {
		system("cls");
		printf("wrong email or username\n");
	}
	else {
		printf("changed sucseufully");
	}
	_sleep(1000);
}
void loginpage(int day) {
	FILE* fp;
	int personality;
	int marizcount;
	int doccount;
	int counter = 0;
	char ch1;
	int i;
	fp = fopen("fmarizcounter.txt", "rb");
	fread(&marizcount, sizeof(int), 1, fp);
	fclose(fp);
	fp = fopen("fdoctorcounter.txt", "rb");
	fread(&doccount, sizeof(int), 1, fp);
	fclose(fp);
	mariz temp2[40];
	doctor temp[10];
	char trash[3];
	int action;
	int working;
	char codemeli[40];
	char password[40];
	system("cls");
	printf("if you want to enter as admin press 1 else press 0\n");
	scanf("%d", &action);
	if (action == 1) {
		printf("enter username and password\nusername:");
		gets_s(trash);
		gets_s(codemeli);
		printf("password:");
		for (i = 0; i < 40; i++)
		{
			ch1 = getch();
			if (ch1 != 13) {     //13 is ASCII of Enter key
				printf("*");
				password[i] = ch1;
			}
			if (ch1 == 13)
				break;
		}
		password[i] = '\0';
		if (strcmp(codemeli, "Admin") == 0 && strcmp(password, "Admin") == 0) {
			counter++;
			adminfirstpage(day);

		}

	}
	else {
		printf("enter username and password\nusername:");
		gets_s(trash);
		gets_s(codemeli);
		printf("password:");
		for (i = 0; i < 40; i++)
		{
			ch1 = getch();
			if (ch1 != 13) {     //13 is ASCII of Enter key
				printf("*");
				password[i] = ch1;
			}
			if (ch1 == 13)
				break;
		}
		password[i] = '\0';
		fp = fopen("fmariz.txt", "rb");
		fread(temp2, sizeof(mariz), 1, fp);
		for (int i = 0; i < marizcount; i++) {
			if (strcmp(temp2[i].codemeli, codemeli) == 0 && strcmp(temp2[i].password, password) == 0) {
				personality = 1;
				working = temp2[i].index - 1;
				counter++;
				marizfirstpage(working, day);
			}
		}
		fclose(fp);
		fp = fopen("fdoctor.txt", "rb");
		fread(temp, sizeof(doctor), doccount, fp);
		for (int i = 0; i < doccount; i++) {
			if (strcmp(temp[i].codemeli, codemeli) == 0 && strcmp(temp[i].password, password) == 0) {
				personality = 2;
				working = temp[i].index - 1;
				counter++;
				doctorfirstpage(working, day);
			}
		}
	}

	if (counter == 0) {
		printf("wrong username or password\n");
		_sleep(1000);
	}

}
void firstpage() {
	int action;
	int x;
	int day;
	int month;
	int year;
	printf("enter the current year then month and then day\n");
	scanf("%d %d %d", &year, &month, &day);
	while (1) {
		system("cls");
		printf("1.sign in\n2.forgot password\n3.exit\n");
		scanf("%d", &action);
		if (action == 1) {
			loginpage(day);
		}
		if (action == 2) {

			forgotpassword();
		}
		if (action == 3) {
			break;
		}
	}

}