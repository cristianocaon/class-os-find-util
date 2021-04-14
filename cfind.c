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
#include <time.h>
char *full_path;

void find_directory(char *dir)
{
  DIR *sub_dp = opendir(dir);
  struct dirent *sub_dirp;

  if (sub_dp != NULL)
  {
    while ((sub_dirp = readdir(sub_dp)) != NULL)
    {
      char *temp = sub_dirp->d_name;
      char temp1[] = ".";
      char temp2[] = "..";

      if (strcmp(temp, temp1) != 0 && strcmp(temp, temp2) != 0) // recurcively loop into the sub-directory
      {
        char temp3[] = "/";
        char *temp_sub = temp3;
        temp_sub = strcat(temp_sub, temp);
        char *temp_full_path = malloc(sizeof(char) * 2000);
        temp_full_path = strcpy(temp_full_path, dir);
        strcat(temp_full_path, temp_sub);
        printf("%s\n", temp_full_path);
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
    printf("Cannot open directory\n");
    exit(2);
  }
}

void find_name(char *dir, char *target, char *action)
{
  DIR *sub_dp = opendir(dir);
  struct dirent *sub_dirp;

  if (sub_dp != NULL)
  {
    while ((sub_dirp = readdir(sub_dp)) != NULL)
    {
      char *temp = sub_dirp->d_name;
      char temp1[] = ".";
      char temp2[] = "..";

      if (strcmp(temp, temp1) != 0 && strcmp(temp, temp2) != 0) // recurcively loop into the sub-directory
      {
        char temp3[] = "/";
        char *temp_sub = temp3;
        temp_sub = strcat(temp_sub, temp);
        char *temp_full_path = malloc(sizeof(char) * 2000);
        temp_full_path = strcpy(temp_full_path, dir);
        strcat(temp_full_path, temp_sub);
        if (strcmp(target, temp) == 0)
        {
          printf("FOUND: %s\n", temp_full_path);
          if (action != NULL)
          {
          }
        }
        DIR *subsubdp = opendir(temp_full_path);
        if (subsubdp != NULL)
        {
          closedir(subsubdp);
          find_name(temp_full_path, target, action);
        }
      }
    }
    closedir(sub_dp);
  }
  else
  {
    printf("Cannot open directory\n");
    exit(2);
  }
}

void find_inum(char *dir, char *inum, char *action)
{
  DIR *sub_dp = opendir(dir);
  struct dirent *sub_dirp;
  struct stat buf;

  if (sub_dp != NULL)
  {
    while ((sub_dirp = readdir(sub_dp)) != NULL)
    {
      char *temp = sub_dirp->d_name;
      char temp1[] = ".";
      char temp2[] = "..";

      if (strcmp(temp, temp1) != 0 && strcmp(temp, temp2) != 0) // recurcively loop into the sub-directory
      {
        char temp3[] = "/";
        char *temp_sub = temp3;
        temp_sub = strcat(temp_sub, temp);
        char *temp_full_path = malloc(sizeof(char) * 2000);
        temp_full_path = strcpy(temp_full_path, dir);
        strcat(temp_full_path, temp_sub);

        if (stat(temp_full_path, &buf) == 0)
        {
          int curr_inum = (int)buf.st_ino;
          if (curr_inum == strtol(inum, NULL, 10))
          {
            printf("FOUND: %s\n", temp_full_path);
            if (action != NULL)
            {
            }
          }
        }

        DIR *subsubdp = opendir(temp_full_path);
        if (subsubdp != NULL)
        {
          closedir(subsubdp);
          find_inum(temp_full_path, inum, action);
        }
      }
    }
    closedir(sub_dp);
  }
  else
  {
    printf("Cannot open directory\n");
    exit(2);
  }
}

void find_mmin(char *dir, char *mmin, char *action)
{
  DIR *sub_dp = opendir(dir);
  struct dirent *sub_dirp;
  struct stat buf;

  if (sub_dp != NULL)
  {
    while ((sub_dirp = readdir(sub_dp)) != NULL)
    {
      char *temp = sub_dirp->d_name;
      char temp1[] = ".";
      char temp2[] = "..";

      if (strcmp(temp, temp1) != 0 && strcmp(temp, temp2) != 0) // recurcively loop into the sub-directory
      {
        char temp3[] = "/";
        char *temp_sub = temp3;
        temp_sub = strcat(temp_sub, temp);
        char *temp_full_path = malloc(sizeof(char) * 2000);
        temp_full_path = strcpy(temp_full_path, dir);
        strcat(temp_full_path, temp_sub);

        memset(&buf, 0, sizeof(buf));
        if (stat(temp_full_path, &buf) == 0)
        {
          if (mmin[0] == '-')
          {
            if ((long)(time(NULL) - buf.st_mtime) < atol(mmin) * -60)
            {
              printf("FOUND: %s\n", temp_full_path);
            }
          }
          else if (mmin[0] == '+')
          {
            if ((long)(time(NULL) - buf.st_mtime) > atol(mmin) * 60)
            {
              printf("FOUND: %s\n", temp_full_path);
            }
          }
          else
          {
            if ((long)(time(NULL) - buf.st_mtime) == atol(mmin) * 60)
            {
              printf("FOUND: %s\n", temp_full_path);
            }
          }
        }

        if (action != NULL)
        {
        }

        DIR *subsubdp = opendir(temp_full_path);
        if (subsubdp != NULL)
        {
          closedir(subsubdp);
          find_mmin(temp_full_path, mmin, action);
        }
      }
    }
    closedir(sub_dp);
  }
  else
  {
    printf("Cannot open directory\n");
    exit(2);
  }
}

int main(int argc, char **argv)
{
  char *dir;
  char *flag;
  char *target;
  char *action;

  if (argc < 2)
  {
    dir = ".";
    find_directory(dir);
  }
  else
  {
    dir = argv[1];
    if (argc == 2)
    {
      printf("DIR: %s\n", dir);
      find_directory(dir);
    }
    else
    {
      flag = argv[2];
      target = argv[3];
      if (argc == 4)
      {
        if (strcmp(flag, "-n") == 0)
        {
          printf("DIR: %s\tTARGET NAME: %s\n", dir, target);
          find_name(dir, target, NULL);
        }
        else if (strcmp(flag, "-mmin") == 0)
        {
          printf("DIR: %s\tTARGET MMIN: %s\n", dir, target);
          find_mmin(dir, target, NULL);
        }
        else if (strcmp(flag, "-inum") == 0)
        {
          printf("DIR: %s\tTARGET INUM: %s\n", dir, target);
          find_inum(dir, target, NULL);
        }
      }
      else if (argc == 5)
      {
        action = argv[4];
        if (strcmp(flag, "-n") == 0)
        {
          printf("DIR: %s\tTARGET NAME: %s\tACTION: %s\n", dir, target, action);
          find_name(dir, target, action);
        }
        else if (strcmp(flag, "-mmin") == 0)
        {
          printf("DIR: %s\tTARGET MMIN: %s\tACTION: %s\n", dir, target, action);
          find_mmin(dir, target, action);
        }
        else if (strcmp(flag, "-inum") == 0)
        {
          printf("DIR: %s\tTARGET INUM: %s\tACTION: %s\n", dir, target, action);
          find_inum(dir, target, action);
        }
      }
    }
  }
  exit(0);
}
