#pragma once


#include "Seat.hpp"

#include <map>
#include <vector>
#include <string>
#include <iosfwd>
#include <memory>
#include <initializer_list>
#include <random>



// Begin of users functions
Theater& order_ticket(Theater&, const std::string& yourName, float& wallet, int seat);
Theater& order_ticket(Theater&, const std::string& yourName, float& wallet, uShort row, uShort rowInSeat);
Theater& order_tickets(Theater&, const std::string& yourName, float& wallet, std::initializer_list<int> seats);
const Theater& check_seat(const Theater&, int seat);
const Theater& check_seat(const Theater&, uShort row, uShort rowInSeat);
const Theater& check_seats(const Theater&, std::initializer_list<int> seats);
Theater& reserve_seat(Theater&, const std::string& yourName, int seat);
Theater& reserve_seat(Theater&, const std::string& yourName, uShort row, uShort rowInSeat);
Theater& reserve_seats(Theater&, const std::string& yourName, std::initializer_list<int> seats);

const Theater& check_theater_seats(std::ostream&, const Theater&);
const Theater& check_theater_types_of_seats(std::ostream&, const Theater&);
Theater& change_stake(Theater&);
Theater& change_price(Theater&);
Theater& random_fill(Theater&);
// End of users functions

std::ostream& operator<<(std::ostream&, const Theater&);

class Theater
{
public:

	Theater(std::string nameOfTheater);
	Theater(std::string nameOfTheater, int seats);
	Theater(std::string nameOfTheater, int seats, uShort rows);
	~Theater();

	// Begin of users functions
	friend Theater& order_ticket(Theater&, const std::string& yourName, float& wallet, int seat);
	friend Theater& order_ticket(Theater&, const std::string& yourName, float& wallet, uShort row, uShort rowInSeat);
	friend Theater& order_tickets(Theater&, const std::string& yourName, float& wallet, std::initializer_list<int> seats);
	friend const Theater& check_seat(const Theater&, int seat);
	friend const Theater& check_seat(const Theater&, uShort row, uShort rowInSeat);
	friend const Theater& check_seats(const Theater&, std::initializer_list<int> seats);
	friend Theater& reserve_seat(Theater&, const std::string& yourName, int seat);
	friend Theater& reserve_seat(Theater&, const std::string& yourName, uShort row, uShort rowInSeat);
	friend Theater& reserve_seats(Theater&, const std::string& yourName, std::initializer_list<int> seats);

	friend const Theater& check_theater_seats(std::ostream&, const Theater&);
	friend const Theater& check_theater_types_of_seats(std::ostream&, const Theater&);
	friend Theater& random_fill(Theater&);
	friend Theater& change_stake(Theater&, const float stake);
	friend Theater& change_price(Theater&, const float price);



	Theater& order_ticket(const std::string& yourName, float& wallet, int seat);
	Theater& order_ticket(const std::string& yourName, float& wallet, uShort row, uShort rowInSeat);
	Theater& order_tickets(const std::string& yourName, float& wallet, std::initializer_list<int> seats);
	const Theater& check_seat(int seat);
	const Theater& check_seat(uShort row, uShort rowInSeat);
	const Theater& check_seats(std::initializer_list<int> seats);
	Theater& reserve_seat(const std::string& yourName, int seat);
	Theater& reserve_seat(const std::string& yourName, uShort row, uShort rowInSeat);
	Theater& reserve_seats(const std::string& yourName, std::initializer_list<int> seats);

	const Theater& check_theater_seats(std::ostream&);
	const Theater& check_theater_types_of_seats(std::ostream&);
	Theater& random_fill();
	Theater& change_stake(const float stake);
	Theater& change_price(const float price);
	
	std::string name() const;
	// End of users functions


	friend std::ostream& operator<<(std::ostream& os, const Theater& t);

private:

	Theater(const Theater& another) = delete;
	Theater& operator=(const Theater& another) = delete;

	Theater(Theater&& another) = delete;
	Theater& operator=(Theater&& another) = delete;


	std::map<int,std::shared_ptr<Seat>> mSeats;
	std::string mName;


	static std::random_device msRDev;
	static std::mt19937 rng;

};