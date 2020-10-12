#!/bin/python3

n = int(input())
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

print('Directory:', user, 'Problem:', tab[user][rnk])
