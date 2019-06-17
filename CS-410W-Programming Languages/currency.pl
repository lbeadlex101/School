#!/usr/bin/perl
# ------------------------------------------------------------------------------
# Lee Beadle
# CS 410W
# Assignment 9 
# Currency Conversion Webpage
# ------------------------------------------------------------------------------
use CGI qw(:standard);
print header;
print start_html("Currency Conversion");
print "<h1> Currency Conversion</h1>\n";

$st = `date`;
chomp($st);

$usDollars = param("usDollars");
$choice = param("currency");

open(FH, ">>currency-log.txt");
open(FD, ">>exchangeRates.txt");

@rates = <FD>;
close $FD;
$pounds = @rates[1];
$euros = @rates[2];
$pesos = @rates[3];
$canadian = @rates[4];

    if($choice eq "P")
    {
        $total = $usDollars * $pounds;
	print "$st   ";
	print FH "$st   ";
        printf ("\$%.2f is %.2f Pounds", $usDollars, $total);
        printf(FH "\$%.2f is %.2f Pounds", $usDollars, $total);
    }

    elsif($choice eq "E")
    {
        $total = $usDollars * $euros;
	print "$st   ";
        print FH "$st   ";
        printf ("\$%.2f is %.2f Euros", $usDollars, $total);
	printf(FH "\$%.2f is %.2f Euros", $usDollars, $total);
    }

    elsif($choice eq "M")
    {
        $total = $usDollars * $pesos;
	print "$st   ";
	print FH "$st   ";
        printf("\$%.2f is %.2f Pesos", $usDollars, $total);
        printf(FH "\$%.2f is %.2f Pesos", $usDollar, $total);	
    }

    elsif($choice eq "C")
    {
        $total = $usDollars * $canadian;
	print "$st   ";
	print FH "$st   ";
        printf("\$%.2f is %.2f Canadian Dollars", $usDollars, $total);
	printf(FH "\$%.2f is %.2f Canadian Dollars", $usDolalrs, $total);
    }

close $FD;    
close $FH;
print end_html;
