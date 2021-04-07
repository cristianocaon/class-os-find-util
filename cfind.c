/*  Author: Cristiano Eleutherio Caon (R#11474435)
    Date: 4/2/2021
    Description: find command utility for UNIX system.
              Developed for Operating System Class (CS 4352)
              with professor Yong Chen. */

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
char *full_path;

void find_directory(char *sub_dir)
{
  DIR *sub_dp = opendir(sub_dir);
  struct dirent *sub_dirp;
  struct stat buf;

  if (sub_dp != NULL)
  {
    while ((sub_dirp = readdir(sub_dp)) != NULL)
    {
      if (strcmp(sub_dirp->d_name, "test1") == 0)
      {
        printf("%s\n", sub_dirp->d_name);
        /*if (stat(sub_dirp->d_name, &buf) == 0)
      {
        printf("%d ", (int)buf.st_size);
      }*/
      }
      char *temp = sub_dirp->d_name;
      char temp1[] = ".";
      char temp2[] = "..";

      if (strcmp(temp, temp1) != 0 && strcmp(temp, temp2) != 0) //recurcively loop into the sub-directory
      {
        char temp3[] = "/";
        char *temp_sub = temp3;
        temp_sub = strcat(temp_sub, temp);
        char *temp_full_path = malloc(sizeof(char) * 2000);
        temp_full_path = strcpy(temp_full_path, sub_dir);
        strcat(temp_full_path, temp_sub);
        DIR *subsubdp = opendir(temp_full_path);
        if (subsubdp != NULL)
        {
          closedir(subsubdp);
          find_directory(temp_full_path);
        }
      }
    }
    closedir(sub_dp);
  }
  else
  {
    printf("cannot open directory\n");
    exit(2);
  }
}

void find_name(char *where, char *name, char *action)
{
  if (action == NULL)
  {
  }
}

void find_inum(char *where, char *inum, char *action)
{
  if (action == NULL)
  {
  }
}

void find_mmin(char *where, char *mmin, char *action)
{
  if (action == NULL)
  {
  }
}

int main(int argc, char **argv)
{
  int w, n, m, i, a;
  char *where, *name, *mmin, *inum, *action;
  while (1)
  {
    char c;

    c = getopt(argc, argv, "w:n:m:i:a:"); /* A colon (‘:’) to
							 * indicate that it
							 * takes a required
							 * argument, e.g, -w
							 * testdir */
    if (c == -1)
    {
      /* We have finished processing all the arguments. */
      break;
    }
    switch (c)
    {
    case 'w':
      w = 1;
      where = optarg;
      printf("where: %s\n", optarg);
      break;
    case 'n':
      n = 1;
      name = optarg;
      printf("name: %s\n", optarg);
      break;
    case 'm':
      m = 1;
      mmin = optarg;
      printf("mmin: %s\n", optarg);
      break;
    case 'i':
      i = 1;
      inum = optarg;
      printf("inum: %s\n", optarg);
      break;
    case 'a':
      a = 1;
      action = optarg;
      printf("action: %s\n", optarg);
      break;
    case '?':
    default:
      printf("An invalid option detected.\n");
    }
  }

  /*
	 * Now you can pass the parameters to the find function. For example,
	 * if the action, where, name are all specified, then you can call
	 * find(where, name, action), but this depends on how you implement
	 * the find function.
	 */

  if (w == 1 && n == 1 && a == 1)
  {
    find_name(where, name, action);
  }
  else if (w == 1 && m == 1 && a == 1)
  {
    find_mmin(where, mmin, action);
  }
  else if (w == 1 && i == 1 && a == 1)
  {
    find_inum(where, inum, action);
  }
  else if (w == 1 && n == 1)
  {
    find_name(where, name, NULL);
  }
  else if (w == 1 && m == 1)
  {
    find_mmin(where, mmin, NULL);
  }
  else if (w == 1 && i == 1)
  {
    find_inum(where, inum, NULL);
  }
  else if (w == 1)
  {
    find_directory(where);
  }

  argc -= optind;
  argv += optind;

  exit(0);
}
