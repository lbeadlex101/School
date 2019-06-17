#!/usr/bin/perl
# Lee Beadle
# CS 410W
# Quiz 3
# -----------------------------------------------------------------------------
print "WHILE LOOP:\n";
$num = 100;
while($num <= 1000)
{
	print "$num\n";
	$num = $num + 100;
}
#------------------------------------------------------------------------------
print "UNTIL LOOP\n";
$num = 100;
until($num > 1000)
{
	print "$num\n";
	$num = $num + 100;
}
#------------------------------------------------------------------------------
print "FOR LOOP\n";
for($num = 100; $num <= 1000; $num = $num + 100)
{
	print "$num\n";
}
#------------------------------------------------------------------------------
print "FOR EACH Loop\n";
for($num = 100; $num <= 1000; $num = $num +100)
{
	push @list, $num;
}
foreach $i (@list)
{
	print "$i\n";
}
#------------------------------------------------------------------------------
print "DO WHILE LOOP\n";
$num = 100;
do 
{
print "$num\n";
$num = $num + 100;
} while ($num <= 1000);
#-----------------------------------------------------------------------------
print "Enter string #1: ";
$str1 = <STDIN>;
chomp($str1);
print "Enter string #2: ";
$str2 = <STDIN>;
chomp($str2);

if($str1 eq $str2)
{
	print "Strings are the same\n";
}

if ($str1 gt $str2)
{
	print "String #1 is greater\n";

}

elsif ($str1 lt $str2)
{
	print "String #2 is greater\n";
}

