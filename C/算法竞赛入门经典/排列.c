#include <stdio.h>

int main ()
{
	int a,b,c,d,e,f,g,h,i;
	int s1, s2, s3;
	for (a = 1; a <= 9; a++)
	{
	for (b = 1; b <= 9; b++)
        {
	for (c = 1; c <= 9; c++)
        {
	for (d = 1; d <= 9; d++)
        {
	for (e = 1; e <= 9; e++)
        {
	for (f = 1; f <= 9; f++)
        {
	for (g = 1; g <= 9; g++)
        {
	for (h = 1; h <= 9; h++)
        {
	for (i = 1; i <= 9; i++)
        {
	s1 = 100*a+10*b+c;
	s2 = 100*d+10*e+f;
	s3 = 100*g+10*h+i;
	if (s3 == 3*s1 && s2 == 2*s1 
	&& a!=b&&a!=c&&a!=d&&a!=e&&a!=f&&a!=g&&a!=h&&a!=i
        && b!=a&&b!=c&&b!=d&&b!=e&&b!=f&&b!=g&&b!=h&&b!=i
        && c!=b&&c!=a&&c!=d&&c!=e&&c!=f&&c!=g&&c!=h&&c!=i
        && d!=b&&d!=c&&d!=a&&d!=e&&d!=f&&d!=g&&d!=h&&d!=i
        && e!=b&&e!=c&&e!=d&&e!=a&&e!=f&&e!=g&&e!=h&&e!=i
        && f!=b&&f!=c&&f!=d&&f!=e&&f!=a&&f!=g&&f!=h&&f!=i
        && g!=b&&g!=c&&g!=d&&g!=e&&g!=f&&g!=a&&g!=h&&g!=i
        && h!=b&&h!=c&&h!=d&&h!=e&&h!=f&&h!=g&&h!=a&&h!=i
        && i!=b&&i!=c&&i!=d&&i!=e&&i!=f&&i!=g&&i!=h&&i!=a)
		printf ("%d %d %d\n", s1, s2, s3);
	}}}}}}}}}}
