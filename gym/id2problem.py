#!/bin/python3

n = int(input("Input problem ID:"))
n -= 101
user = n // 4
rnk = n % 4

tab = [
['UC','DG','RB',''],
['HC','IB','FJ',''],
['GK','UH','QH',''],
['EE','DJ','IH',''],
['HL','MI','EJ',''],
['MB','UI','ED',''],
['AA','BG','ML',''],
['CF','TE','QG',''],
['PH','UJ','BB',''],
['CI','SD','NG',''],
['DK','LD','IJ',''],
['NC','BJ','FK',''],
['CH','NJ','RH',''],
['QF','BE','KI',''],
['AC','PG','HM',''],
['PJ','ID','EG',''],
['SI','KC','GI',''],
['OG','CK','DB',''],
['QE','GH','NI',''],
['OL','KA','MG',''],
['SG','NL','KH',''],
['QJ','KG','AB',''],
['KD','IL','NF',''],
['CM','NE','HD',''],
['DH','EC','BM',''],
['LC','CD','JI',''],
['DL','ME','PE',''],
['LI','AI','RJ',''],
['SF','II','HG',''],
['RE','LL','OA',''],
['FB','QD','DA',''],
['TC','AE','CB',''],
['GF','AG','JC',''],
['PA','TH','EH',''],
['AJ','TK','EI',''],
['UL','AF','SK',''],
['BH','RD','OK',''],
['FC','JD','OE',''],
['TF','FF','DD',''],
['CJ','HK','MJ',''],
['FG','GL','AL',''],
['FI','IC','QC',''],
['MD','OJ','HI',''],
['KK','JH','OB',''],
['BK','GJ','KE',''],
['CA','IK','LE',''],
['RI','LK','PD',''],
['JE','LB','HB',''],
['BL','RG','AH',''],
['AK','GG','JG','']
]

link = [
["https://codeforces.com/gym/101221", "statements/2014-acmicpc-world-finals-en.pdf"],
["https://codeforces.com/gym/101239", "statements/2015-acmicpc-world-finals-en.pdf"],
["https://codeforces.com/gym/101242", "statements/2016-acmicpc-world-finals-en.pdf"],
["https://codeforces.com/gym/101471", "statements/2017-acmicpc-world-finals-en.pdf"],
["https://codeforces.com/gym/102482", "statements/2018-acmicpc-world-finals-en.pdf"],
["https://codeforces.com/gym/102511", "statements/2019-acmicpc-world-finals-en.pdf"],
["https://codeforces.com/gym/101630", "statements/20172018-acmicpc-northeastern-european-regional-contest-neerc-17-en.pdf"],
["https://codeforces.com/gym/101190", "statements/20162017-acmicpc-northeastern-european-regional-contest-neerc-16-en.pdf"],
["https://codeforces.com/gym/100851", "statements/20152016-acmicpc-northeastern-european-regional-contest-neerc-15-en.pdf"],
["https://codeforces.com/gym/100553", "statements/20142015-acmicpc-northeastern-european-regional-contest-neerc-14-en.pdf"],
["https://codeforces.com/gym/100307", "statements/20132014-acmicpc-northeastern-european-regional-contest-neerc-13-en.pdf"],
["https://codeforces.com/gym/101620", "statements/20172018-acmicpc-central-europe-regional-contest-cerc-17-en.pdf"],
["https://codeforces.com/gym/101173", "statements/20162017-acmicpc-central-europe-regional-contest-cerc-16-en.pdf"],
["https://codeforces.com/gym/101480", "statements/20152016-acmicpc-central-europe-regional-contest-cerc-15-en.pdf"],
["https://codeforces.com/gym/100543", "statements/20142015-acmicpc-central-europe-regional-contest-cerc-14-en.pdf"],
["https://codeforces.com/gym/100299", "statements/20132014-acm-icpc-central-european-regional-contest-cerc-13-en.pdf"],
["https://codeforces.com/gym/101612", "statements/20172018-acmicpc-neerc-northern-subregional-contest-en.pdf"],
["https://codeforces.com/gym/101142", "statements/20162017-acmicpc-neerc-northern-subregional-contest-en.pdf"],
["https://codeforces.com/gym/100801", "statements/20152016-acmicpc-neerc-northern-subregional-contest-en.pdf"],
["https://codeforces.com/gym/100531", "statements/20142015-acmicpc-neerc-northern-subregional-contest-en.pdf"],
["https://codeforces.com/gym/100269", "statements/20132014-acmicpc-neerc-nothern-subregional-contest-en.pdf"]
]
pr = tab[user][rnk]
print('Directory:', user, 'Problem:', tab[user][rnk])
if pr != '':
    id = ord(pr[0]) - ord('A')
    print('Submit:', link[id][0] + '/submit/' + pr[1])
    print('Statement:', 'xdg-open ./' + link[id][1])
