#!/usr/bin/perl

while(my $line = <>)
{
	chomp $line;
	$line=~ s/ͼƬ$|��Ƶ$//;
	print $line."\n";
}
