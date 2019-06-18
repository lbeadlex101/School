#!/usr/bin/perl
#-------------------------------------------------------------------------------
# Lee Beadle
# CS410W
# Assignment #10
# This program generates random numbers based on three command line arguments of
# min, max, and count. Command options -d and -s are included to change the output 
# to decimal numbers(-d) or sum the numbers(-s).  
#-------------------------------------------------------------------------------
use Getopt::Std;

if(! getopts('sd'))
{
	die "Usage: assign10.pl -sd\n";
}

$min = $ARGV[0];
$max = $ARGV[1];
$count = $ARGV[2];
$numArgs = @ARGV;

if($numArgs != 3)
{
    	print "You need 3 arguments: min max count\n";
}

elsif($max < $min)
{
    	print "Max cannot be smaller than min\n";
}

else
{
	if($opt_d)
	{
		for($i = 0; $i < $count; $i = $i + 1)
		{
        		$num = $min + rand($max - $min);
        		print "$num\n";
    		}
	}

	if($opt_s)
	{	
		for($i = 0; $i < $count; $i = $i + 1)
		{
        		$num = $min + int(rand($max - $min));
			$sum = $num + $sum;
        		print "$num\n";
    		}

		print "SUM: $sum\n";
	}

	if($opt_d && $opt_s)
	{	
		for($i = 0; $i < $count; $i = $i + 1)
		{
        		$num = $min + rand($max - $min);
			$sum = $num + $sum;
        		print "$num\n";
    		}

		print "SUM: $sum\n";
	}

}
