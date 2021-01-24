-- Keep a log of any SQL queries you execute as you solve the mystery.
/* All you know is that the theft took place on July 28, 2020 and that it took place on Chamberlin Street. */
-- Check all crime reports from 7/28 on Chamberlin Street
SELECT description FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND
street = "Chamberlin Street";
/* Crime Description:
                    Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. 
                    Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.
:View the transcripts of the interviews*/
SELECT transcript FROM interviews
WHERE month = 7 AND day = 28
AND transcript like "%courthouse%"
/*  Transcript 1:
                    Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. 
                    If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
    Transcript 2:
                    I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, 
                    I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money
    Transcript 3:
                    As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, 
                    I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. 
                    The thief then asked the person on the other end of the phone to purchase the flight ticket.
*/
-- List people who left the courthouse around that time
SELECT name, phone_number, passport_number FROM courthouse_security_logs
JOIN people ON courthouse_security_logs.license_plate = people.license_plate                /* Name: Ernest	    Phone: (367) 555-5533	    Passport: 5773159633 */
WHERE day = 28 AND hour = 10 AND activity = "exit"
-- List people who used the atm that morning
SELECT name from atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number        /* Ernest */
JOIN people ON bank_accounts.person_id = people.id
WHERE month = 7 AND day = 28 AND atm_location = "Fifer Street"
-- Check first flight out of Fiftyville the next morning
SELECT airports.full_name, flights.id FROM flights
JOIN airports ON flights.destination_airport_id = airports.id                               /* Heathrow Airport / London / Flight:36 */
WHERE month = 7 AND day = 29 AND flights.origin_airport_id = 8
ORDER BY hour LIMIT 1;
-- Check flight 36
SELECT passport_number from passengers                                                      /* Passport: 5773159633 */
WHERE flight_id = 36
-- Check Ernest calls that day for Accomplice
SELECT name FROM phone_calls
JOIN people ON phone_calls.receiver = people.phone_number
WHERE caller = "(367) 555-5533" AND day = 28 AND duration < 60