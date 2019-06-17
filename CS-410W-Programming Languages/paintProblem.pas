{------------------------------------------------------------------------------}
{
Lee Beadle
CS 410W
Pascal Paint Cost Program
}
{------------------------------------------------------------------------------}
{Program info, libraries, and variables}
PROGRAM Paint_Cost;
USES Math;
CONST
HEIGHT = 8;
ONE_GALLON = 350;
VAR
room_type      : STRING;
length         : REAL;
width          : REAL;
can_cost       : REAL;
surface_area   : REAL;
num_of_gallons : REAL;
num_of_cans    : INTEGER;
total_cost     : REAL;
{------------------------------------------------------------------------------}
{Read User Input Procedure}
PROCEDURE read_input;
BEGIN
    Write('Enter the room type: ');
    Readln(room_type);
    Write('Enter the room length: ');
    Readln(length);
    Write('Enter the room width: ');
    Readln(width);
    Write('Enter the cost of one can of paint: $');
    Readln(can_cost);
END;
{------------------------------------------------------------------------------}
{Calculate Surface Area Function}
FUNCTION calc_surface_area(length: REAL; width: REAL; height: REAL) : REAL;
BEGIN
    calc_surface_area := (length*width) + 2*(length*height) + 2*(width*height);
END;
{------------------------------------------------------------------------------}
{Calculate Number of Gallons Function}
FUNCTION calc_num_gallons(surface_area: REAL; a_gallon: integer): REAL;
BEGIN
    calc_num_gallons := surface_area / a_gallon;
END;
{------------------------------------------------------------------------------}
{Calculate Numeber of Cans Function}
FUNCTION calc_num_cans(num_of_gallons: REAL): INTEGER;
BEGIN
    calc_num_cans := Ceil(num_of_gallons);
END;    
{------------------------------------------------------------------------------}
{Calculate Total Cost Function}
FUNCTION calc_total_cost(num_of_cans: INTEGER; can_cost: REAL): REAL;
BEGIN
    calc_total_cost := num_of_cans * can_cost;
END;
{------------------------------------------------------------------------------}
{Output Results Procedure}
PROCEDURE display_results;
BEGIN
    Writeln('Room type: ', room_type);
    Writeln('Surface area (minus floor): ', surface_area:0:1, ' sq ft');
    Writeln('Number of gallons: ', num_of_gallons:0:3);
    Writeln('Number of cans: ', num_of_cans:0);
    Writeln('Total Cost: $', total_cost:0:2);
END;
{------------------------------------------------------------------------------}
{Main Driver}
BEGIN
    read_input;
    surface_area := calc_surface_area(length, width, HEIGHT);
    num_of_gallons:= calc_num_gallons(surface_area, ONE_GALLON);
    num_of_cans := calc_num_cans(num_of_gallons);
    total_cost := calc_total_cost(num_of_cans, can_cost);
    display_results; 
END.
{------------------------------------------------------------------------------}