{------------------------------------------------------------------------------}
{
Lee Beadle
CS 410W
Pascal Paint Cost Program
MODIFIED Assignment #5
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
room_cost      : REAL;
answer         : CHAR;
is_one_room    : BOOLEAN;
previous_room  : REAL;
running_total  : REAL;
most_exp_cost  : REAL;
most_exp_room  : STRING;
total_cost     : REAL;
{------------------------------------------------------------------------------}
{Read User Input Procedure}
PROCEDURE read_input(var room: STRING; var length: REAL; var width: REAL; 
                     var cost : REAL);
BEGIN
    Write('Enter the room type: ');
    Readln(room);
    Write('Enter the room length: ');
    Readln(length);
    Write('Enter the room width: ');
    Readln(width);
    Write('Enter the cost of one can of paint: $');
    Readln(cost);
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
FUNCTION calc_room_cost(num_of_cans: INTEGER; can_cost: REAL): REAL;
BEGIN
    calc_room_cost := num_of_cans * can_cost;
END;
{------------------------------------------------------------------------------}
{Outputs One Room Results Procedure}
PROCEDURE display_one_results;
BEGIN
    Writeln('Room type: ', room_type);
    Writeln('Surface area (minus floor): ', surface_area:0:1, ' sq ft');
    Writeln('Number of gallons: ', num_of_gallons:0:3);
    Writeln('Number of cans: ', num_of_cans:0);
    Writeln('Room Cost: $', room_cost:0:2);
END;
{------------------------------------------------------------------------------}
{Output Muliple Rooms Results Procedure}
PROCEDURE display_mulitple_results;
BEGIN
    Writeln('Most Expensive Room: ', most_exp_room);
    Writeln('Expensive Room Cost: $', most_exp_cost:0:2);
    Writeln('Total Paint Cost: $', total_cost:0:2);
END;
{------------------------------------------------------------------------------}
PROCEDURE calc_one_room;
BEGIN
    surface_area := calc_surface_area(length, width, HEIGHT);
    num_of_gallons:= calc_num_gallons(surface_area, ONE_GALLON);
    num_of_cans := calc_num_cans(num_of_gallons);
    room_cost := calc_room_cost(num_of_cans, can_cost);
END;
{------------------------------------------------------------------------------}
{Main Driver}
BEGIN
    previous_room := 0;
    running_total := 0;
    most_exp_cost := 0;
    total_cost := 0;
    
    read_input(room_type, length, width, can_cost);
    calc_one_room;
    previous_room := room_cost;
    Write('Would you like to enter more rooms (y/n): ');
    Readln(answer);
    
    IF (answer = 'n') THEN
        is_one_room := true
    ELSE
        REPEAT
            is_one_room := false;
            calc_one_room;
            
            if (room_cost >= previous_room) THEN
                most_exp_room := room_type;
                most_exp_cost := room_cost;
                
            read_input(room_type, length, width, can_cost);
            calc_one_room; 
            Write('Would you like to enter more rooms (y/n): ');
            Readln(answer);
            running_total := room_cost + previous_room;
            previous_room := room_cost;
        UNTIL (answer = 'n'); 
    
    total_cost := total_cost + running_total;

    If(is_one_room = true) THEN
        display_one_results;
    
    IF(is_one_room = false) THEN
        display_mulitple_results;
END.
{------------------------------------------------------------------------------}