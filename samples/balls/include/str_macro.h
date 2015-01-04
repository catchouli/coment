#pragma once

#define MAX_CONST_CHAR 100

#define MIN(a,b) (a)<(b)?(a):(b)

template <char... chars>
struct str
{

};

#define _T(s)\
getChr(s,0),\
getChr(s,1),\
getChr(s,2),\
getChr(s,3),\
getChr(s,4),\
getChr(s,5),\
getChr(s,6),\
getChr(s,7),\
getChr(s,8),\
getChr(s,9),\
getChr(s,10),\
getChr(s,11),\
getChr(s,12),\
getChr(s,13),\
getChr(s,14),\
getChr(s,15),\
getChr(s,16),\
getChr(s,17),\
getChr(s,18),\
getChr(s,19),\
getChr(s,20),\
getChr(s,21),\
getChr(s,22),\
getChr(s,23),\
getChr(s,24),\
getChr(s,25),\
getChr(s,26),\
getChr(s,27),\
getChr(s,28),\
getChr(s,29),\
getChr(s,30),\
getChr(s,31),\
getChr(s,32),\
getChr(s,33),\
getChr(s,34),\
getChr(s,35),\
getChr(s,36),\
getChr(s,37),\
getChr(s,38),\
getChr(s,39),\
getChr(s,40),\
getChr(s,41),\
getChr(s,42),\
getChr(s,43),\
getChr(s,44),\
getChr(s,45),\
getChr(s,46),\
getChr(s,47),\
getChr(s,48),\
getChr(s,49),\
getChr(s,50),\
getChr(s,51),\
getChr(s,52),\
getChr(s,53),\
getChr(s,54),\
getChr(s,55),\
getChr(s,56),\
getChr(s,57),\
getChr(s,58),\
getChr(s,59),\
getChr(s,60),\
getChr(s,61),\
getChr(s,62),\
getChr(s,63),\
getChr(s,64),\
getChr(s,65),\
getChr(s,66),\
getChr(s,67),\
getChr(s,68),\
getChr(s,69),\
getChr(s,70),\
getChr(s,71),\
getChr(s,72),\
getChr(s,72),\
getChr(s,72),\
getChr(s,73),\
getChr(s,74),\
getChr(s,75),\
getChr(s,76),\
getChr(s,77),\
getChr(s,78),\
getChr(s,79),\
getChr(s,80),\
getChr(s,81),\
getChr(s,82),\
getChr(s,83),\
getChr(s,84),\
getChr(s,85),\
getChr(s,86),\
getChr(s,87),\
getChr(s,88),\
getChr(s,89),\
getChr(s,90),\
getChr(s,91),\
getChr(s,92),\
getChr(s,93),\
getChr(s,94),\
getChr(s,95),\
getChr(s,96),\
getChr(s,97),\
getChr(s,98),\
getChr(s,99),\
getChr(s,100)

#define getChr(name, ii) ((MIN(ii,MAX_CONST_CHAR))<strlen(name)?name[ii]:0)