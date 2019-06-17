#!/usr/bin/perl
#-------------------------------------------------------------------------------
# Lee Beadle
# CS410W
# Assignment #10
# NOTE: Does not work with command line options. 
#-------------------------------------------------------------------------------
use Getopt::Std;

getopts("sd", \%opts);

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
    for($i = 0; $i < $count; $i = $i + 1)
    {
        $num = $min + int(rand($max - $min));
        print "$num\n";
    }
}
