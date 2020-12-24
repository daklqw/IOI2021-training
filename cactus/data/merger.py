#!/bin/python3
import os
def getsubtasks(path):
    res, rml = [], []
    for x in os.listdir(path):
        tmp = os.path.join(path, x)
        if os.path.isdir(tmp):
            res.append(tmp)
    res.sort()
    return res
def gettasks(path):
    res = []
    for x in os.listdir(path):
        tmp = os.path.join(path, x)
        if os.path.isfile(tmp):
            if len(tmp) >= 3 and tmp[-3:] == '.in':
                res.append(tmp[:-3])
    res.sort()
    return res
def runexec(str):
    print('exec ', str)
    if os.system(str) != 0:
        print('An error occurred, exit.')
        exit(-1)
prefix = input('prefix: ')
F = open('subtask.conf', 'w')
basepath = './'
dirc = getsubtasks(basepath)
subtaskc = len(dirc)
print('n_subtasks', subtaskc, file = F)
for i in range(subtaskc):
    print('subtask_score_' + str(i + 1), 0, file = F)
print('Get', subtaskc, 'subtask(s)')
havval = True
if not os.path.isfile('./val'):
    havval = False
    print('Warning: No val')
nc, tc = 0, 0
for sub in dirc:
    print('in', sub)
    task = gettasks(sub)
    for f in task:
        nc += 1
        filename = prefix + str(nc)
        runexec('cp ' + f + '.in ' + filename + '.in')
        runexec('time ./std  < ' + filename + '.in > ' + f + '.ans')
        runexec('cp ' + f + '.ans ' + filename + '.ans')
        runexec(sub + '/val < ' + filename + '.in')
        runexec('./val < ' + filename + '.in')
        print('Check', nc, 'OK')
    tc += 1
    print('subtask_end_' + str(tc), nc, file = F)
print(nc, 'test(s) in total')
print('n_tests', nc, file = F)
F.close()
