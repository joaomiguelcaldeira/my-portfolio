#!/usr/bin/python3

files = """
-rw-r--r-- 1 bernardo users   35 May 17 16:47 A-01-1-N-ok.fir
-rw-r--r-- 1 bernardo users   38 May 17 16:47 A-02-2-N-ok.fir
-rw-r--r-- 1 bernardo users   50 May 17 16:47 A-03-3-N-ok.fir
-rw-r--r-- 1 bernardo users   46 May 17 16:47 A-04-4-N-ok.fir
-rw-r--r-- 1 bernardo users   36 May 17 16:47 B-01-5-N-ok.fir
-rw-r--r-- 1 bernardo users   38 May 17 16:47 B-02-6-N-ok.fir
-rw-r--r-- 1 bernardo users   39 May 17 16:47 B-03-7-N-ok.fir
-rw-r--r-- 1 bernardo users   38 May 17 16:47 B-04-8-N-ok.fir
-rw-r--r-- 1 bernardo users   40 May 17 16:47 B-05-9-N-ok.fir
-rw-r--r-- 1 bernardo users   40 May 17 16:47 B-06-10-N-ok.fir
-rw-r--r-- 1 bernardo users   40 May 17 16:47 B-07-11-N-ok.fir
-rw-r--r-- 1 bernardo users   37 May 17 16:47 B-08-12-N-ok.fir
-rw-r--r-- 1 bernardo users   37 May 17 16:47 B-09-13-N-ok.fir
-rw-r--r-- 1 bernardo users   38 May 17 16:47 B-10-14-N-ok.fir
-rw-r--r-- 1 bernardo users   38 May 17 16:47 B-11-15-N-ok.fir
-rw-r--r-- 1 bernardo users   38 May 17 16:47 B-12-16-N-ok.fir
-rw-r--r-- 1 bernardo users   37 May 17 16:47 B-13-17-N-ok.fir
-rw-r--r-- 1 bernardo users   47 May 17 16:47 B-14-18-N-ok.fir
-rw-r--r-- 1 bernardo users   47 May 17 16:47 B-15-19-N-ok.fir
-rw-r--r-- 1 bernardo users   35 May 17 16:47 B-16-20-N-ok.fir
-rw-r--r-- 1 bernardo users   36 May 17 16:47 B-17-21-N-ok.fir
-rw-r--r-- 1 bernardo users   61 May 17 16:47 B-20-22-N-ok.fir
-rw-r--r-- 1 bernardo users   61 May 17 16:47 B-21-23-N-ok.fir
-rw-r--r-- 1 bernardo users   66 May 17 16:47 B-22-24-N-ok.fir
-rw-r--r-- 1 bernardo users   66 May 17 16:47 B-23-25-N-ok.fir
-rw-r--r-- 1 bernardo users   36 May 17 16:47 B-24-26-N-ok.fir
-rw-r--r-- 1 bernardo users   43 May 17 16:47 B-25-27-N-ok.fir
-rw-r--r-- 1 bernardo users   40 May 17 16:47 C-01-28-N-ok.fir
-rw-r--r-- 1 bernardo users   42 May 17 16:47 C-02-29-N-ok.fir
-rw-r--r-- 1 bernardo users   49 May 17 16:47 C-03-30-N-ok.fir
-rw-r--r-- 1 bernardo users   45 May 17 16:47 C-04-31-N-ok.fir
-rw-r--r-- 1 bernardo users   62 May 17 16:47 C-05-32-N-ok.fir
-rw-r--r-- 1 bernardo users   53 May 17 16:47 C-06-33-N-ok.fir
-rw-r--r-- 1 bernardo users   55 May 17 16:47 C-07-34-N-ok.fir
-rw-r--r-- 1 bernardo users   56 May 17 16:47 C-08-35-N-ok.fir
-rw-r--r-- 1 bernardo users   56 May 17 16:47 C-09-36-N-ok.fir
-rw-r--r-- 1 bernardo users   58 May 17 16:47 C-10-37-N-ok.fir
-rw-r--r-- 1 bernardo users   58 May 17 16:47 C-11-38-N-ok.fir
-rw-r--r-- 1 bernardo users   58 May 17 16:47 C-12-39-N-ok.fir
-rw-r--r-- 1 bernardo users   58 May 17 16:47 C-13-40-N-ok.fir
-rw-r--r-- 1 bernardo users   66 May 17 16:47 C-14-41-N-ok.fir
-rw-r--r-- 1 bernardo users   66 May 17 16:47 C-15-42-N-ok.fir
-rw-r--r-- 1 bernardo users   60 May 17 16:47 C-16-43-N-ok.fir
-rw-r--r-- 1 bernardo users   83 May 17 16:47 C-17-44-N-ok.fir
-rw-r--r-- 1 bernardo users   83 May 17 16:47 C-18-45-N-ok.fir
-rw-r--r-- 1 bernardo users  104 May 17 16:47 D-01-46-N-ok.fir
-rw-r--r-- 1 bernardo users  210 May 17 16:47 D-02-47-N-ok.fir
-rw-r--r-- 1 bernardo users  211 May 17 16:47 D-03-48-N-ok.fir
-rw-r--r-- 1 bernardo users   89 May 17 16:47 D-04-49-N-ok.fir
-rw-r--r-- 1 bernardo users   90 May 17 16:47 D-05-50-N-ok.fir
-rw-r--r-- 1 bernardo users  102 May 17 16:47 D-06-51-N-ok.fir
-rw-r--r-- 1 bernardo users   89 May 17 16:47 D-07-52-N-ok.fir
-rw-r--r-- 1 bernardo users  117 May 17 16:47 D-08-53-N-ok.fir
-rw-r--r-- 1 bernardo users  141 May 17 16:47 D-09-54-N-ok.fir
-rw-r--r-- 1 bernardo users  204 May 17 16:47 D-10-55-N-ok.fir
-rw-r--r-- 1 bernardo users  184 May 17 16:47 D-11-56-N-ok.fir
-rw-r--r-- 1 bernardo users  231 May 17 16:47 D-12-57-N-ok.fir
-rw-r--r-- 1 bernardo users  214 May 17 16:47 D-13-58-N-ok.fir
-rw-r--r-- 1 bernardo users   54 May 17 16:47 E-01-59-N-ok.fir
-rw-r--r-- 1 bernardo users   50 May 17 16:47 E-02-60-N-ok.fir
-rw-r--r-- 1 bernardo users   60 May 17 16:47 E-03-61-N-ok.fir
-rw-r--r-- 1 bernardo users   72 May 17 16:47 E-04-62-N-ok.fir
-rw-r--r-- 1 bernardo users   58 May 17 16:47 E-05-63-N-ok.fir
-rw-r--r-- 1 bernardo users   63 May 17 16:47 E-06-64-N-ok.fir
-rw-r--r-- 1 bernardo users   85 May 17 16:47 E-07-65-N-ok.fir
-rw-r--r-- 1 bernardo users   70 May 17 16:47 E-08-66-N-ok.fir
-rw-r--r-- 1 bernardo users   55 May 17 16:47 E-09-67-N-ok.fir
-rw-r--r-- 1 bernardo users   87 May 17 16:47 F-01-68-N-ok.fir
-rw-r--r-- 1 bernardo users   54 May 17 16:47 F-02-69-N-ok.fir
-rw-r--r-- 1 bernardo users   63 May 17 16:47 F-03-70-N-ok.fir
-rw-r--r-- 1 bernardo users   70 May 17 16:47 F-04-71-N-ok.fir
-rw-r--r-- 1 bernardo users   68 May 17 16:47 F-05-72-N-ok.fir
-rw-r--r-- 1 bernardo users  117 May 17 16:47 F-06-73-N-ok.fir
-rw-r--r-- 1 bernardo users  122 May 17 16:47 F-07-74-N-ok.fir
-rw-r--r-- 1 bernardo users  120 May 17 16:47 F-08-75-N-ok.fir
-rw-r--r-- 1 bernardo users  115 May 17 16:47 F-09-76-N-ok.fir
-rw-r--r-- 1 bernardo users  117 May 17 16:47 G-01-77-N-ok.fir
-rw-r--r-- 1 bernardo users  177 May 17 16:47 G-02-78-N-ok.fir
-rw-r--r-- 1 bernardo users  174 May 17 16:47 G-03-79-N-ok.fir
-rw-r--r-- 1 bernardo users   82 May 17 16:47 H-01-80-N-ok.fir
-rw-r--r-- 1 bernardo users   66 May 17 16:47 H-02-81-N-ok.fir
-rw-r--r-- 1 bernardo users   87 May 17 16:47 I-01-82-N-ok.fir
-rw-r--r-- 1 bernardo users   70 May 17 16:47 I-02-83-N-ok.fir
-rw-r--r-- 1 bernardo users   67 May 17 16:47 I-03-84-N-ok.fir
-rw-r--r-- 1 bernardo users   98 May 17 16:47 J-01-85-N-ok.fir
-rw-r--r-- 1 bernardo users   88 May 17 16:47 J-02-86-N-ok.fir
-rw-r--r-- 1 bernardo users   95 May 17 16:47 J-03-87-N-ok.fir
-rw-r--r-- 1 bernardo users  106 May 17 16:47 J-04-88-N-ok.fir
-rw-r--r-- 1 bernardo users   95 May 17 16:47 K-01-89-N-ok.fir
-rw-r--r-- 1 bernardo users  124 May 17 16:47 K-02-90-N-ok.fir
-rw-r--r-- 1 bernardo users  320 May 17 16:47 K-03-91-N-ok.fir
-rw-r--r-- 1 bernardo users  193 May 17 16:47 K-04-92-N-ok.fir
-rw-r--r-- 1 bernardo users   86 May 17 16:47 K-05-93-N-ok.fir
-rw-r--r-- 1 bernardo users  128 May 17 16:47 K-06-94-N-ok.fir
-rw-r--r-- 1 bernardo users  145 May 17 16:47 K-07-95-N-ok.fir
-rw-r--r-- 1 bernardo users  171 May 17 16:47 M-01-96-N-ok.fir
-rw-r--r-- 1 bernardo users  176 May 17 16:47 M-02-97-N-ok.fir
-rw-r--r-- 1 bernardo users  156 May 17 16:47 O-01-98-N-ok.fir
-rw-r--r-- 1 bernardo users  161 May 17 16:47 O-02-99-N-ok.fir
-rw-r--r-- 1 bernardo users  202 May 17 16:47 P-01-100-N-ok.fir"""

TEST_DIRECTORY = "tests-fir-daily-202105171721"


# print("#!/bin/bash")
print("cd fir; make clean; make; cd ..")
for line in files.splitlines():
    test_name = line.split(" ")[-1]
    print(f"fir/fir {TEST_DIRECTORY}/{test_name} --target xml")
    print(f"echo {test_name}")


print("cd fir; make clean; cd ..")
print(f"{TEST_DIRECTORY}/*.xml {TEST_DIRECTORY}/.xml")