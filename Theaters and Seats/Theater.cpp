#include "Theater.hpp"
#include <cmath>
#include <string>
#include <iostream>
#include <random>
#include <chrono>
#include <sstream>
#include <iomanip>

std::random_device Theater::msRDev{};
std::mt19937 Theater::rng(Theater::msRDev() ^ (
	static_cast<std::mt19937::result_type>(
		std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::system_clock::now().time_since_epoch()
			).count())));;

const Theater& check_seat(const Theater& t, int seat)
{
	std::cout << t.mSeats.at(seat)->whatSeat() << " #" << seat << " from the theater \"" << t.mName << "\" is " <<
		(t.mSeats.at(seat)->mBought ? "occupied by " + t.mSeats.at(seat)->mWho :
			t.mSeats.at(seat)->mReserved ? "reserved by " + t.mSeats.at(seat)->mWho : "empty") << std::endl;
	return t;
}
const Theater& check_seat(const Theater& t, uShort row, uShort rowInSeat)
{
	int seat = 0;
	for (auto x : t.mSeats)
	{
		++seat;
		if (x.second->mRow == row)
			if (x.second->mRow == rowInSeat)
				break;
	}

	return check_seat(t,seat);
}
const Theater& check_seats(const Theater& t, std::initializer_list<int> seats)
{
	for (auto seat : seats)
		check_seat(t, seat);
	return t;
}

Theater& order_ticket(Theater& t, const std::string& yourName, float& wallet, int seat)
{
	float price = t.mSeats.at(seat)->mPrice;
	if (t.mSeats[seat]->mBought)
	{
		std::cout << t.mSeats[seat]->whatSeat() << " #" << seat << " from the theater \"" << t.mName <<
			"\" is occupied by " << t.mSeats[seat]->mWho << ", please choose different seat." << std::endl;
		return t;
	}
	else {
		if (t.mSeats[seat]->mReserved)
		{
			std::cout << t.mSeats[seat]->whatSeat() << " #" << seat << " from the theater \"" << t.mName
				<< "\" is reserved by " << t.mSeats[seat]->mWho << ", although it can be bought out for x1.5 price." << std::endl;
			std::cout << "Do you want to buy out? (type: 'yes' or 'no')" << std::endl;
			std::string answer = {};
			std::cin >> answer;
			if (!(answer[0] == 'y' || answer[0] == 'Y'))
				return t;
			price *= 1.5f;
		}
		if (price > wallet) {
			std::cout << "Don't enough money in wallet, purchace is denied." << std::endl;
			return t;
		}
		wallet = wallet - price;
		t.mSeats[seat]->mBought = true;
		t.mSeats[seat]->mWho = yourName;
		std::cout << "Ticket for " << t.mSeats[seat]->whatSeat() << " #" << seat << " ordered." << std::endl;
		return t;
	}
}
Theater& order_ticket(Theater& t, const std::string& yourName, float& wallet, uShort row, uShort rowInSeat)
{
	int seat = 0;
	for (auto x : t.mSeats)
	{
		++seat;
		if (x.second->mRow == row)
			if (x.second->mRow == rowInSeat)
				break;
	}

	return order_ticket(t, yourName, wallet, seat);
}
Theater& order_tickets(Theater& t, const std::string& yourName, float& wallet, std::initializer_list<int> seats)
{
	for (auto seat : seats)
		order_ticket(t, yourName, wallet, seat);
	return t;
}

Theater& reserve_seat(Theater& t, const std::string& yourName, int seat)
{
	if (t.mSeats[seat]->mBought)
	{
		std::cout << t.mSeats[seat]->whatSeat() << " #" << seat << " from the theater \"" << t.mName <<
			"\" is occupied by " << t.mSeats[seat]->mWho << ", please choose different seat." << std::endl;
		return t;
	}
	else {
		if (t.mSeats[seat]->mReserved)
		{
			std::cout << t.mSeats[seat]->whatSeat() << " #" << seat << " from the theater \"" << t.mName
				<< "\" is reserved by " << t.mSeats[seat]->mWho << std::endl;
			std::cout << "Seat can be bought out for x1.5 price. Order ticket for this action." << std::endl;
				return t;
		}
		t.mSeats[seat]->mReserved = true;
		t.mSeats[seat]->mWho = yourName;
		std::cout << t.mSeats[seat]->whatSeat() << " #" << seat << " is reserved for " << yourName << std::endl;
		return t;
	}
}
Theater& reserve_seat(Theater& t, const std::string& yourName, uShort row, uShort rowInSeat)
{
	int seat = 0;
	for (auto x : t.mSeats)
	{
		++seat;
		if (x.second->mRow == row)
			if (x.second->mRow == rowInSeat)
				break;
	}

	return reserve_seat(t, yourName, seat);
}
Theater& reserve_seats(Theater& t, const std::string& yourName, std::initializer_list<int> seats)
{
	for (auto seat : seats)
		reserve_seat(t, yourName, seat);
	return t;
}


const Theater& check_theater_seats(std::ostream& os, const Theater& t)
{
	os << t;
	return t;
}
const Theater& check_theater_types_of_seats(std::ostream& os, const Theater& t)
{
	os << "The theater \"" << t.mName << "\" has following seats:\n\t(For the last row focus on numbers below)\n  \t";
	std::ostringstream nextLine{};
	nextLine << "  \t  ";
	for (auto topNumbers : t.mSeats)
	{
		if (topNumbers.second->mRow == 2)
			break;
		if (topNumbers.second->mSeatInRow % 2)
			os << std::left << std::setw(4) << std::to_string(topNumbers.second->mSeatInRow) + ".";
		else
			nextLine << std::left << std::setw(4) << std::to_string(topNumbers.second->mSeatInRow) + ".";
	}
	os << "\b\n" << nextLine.str() << std::endl;

	auto lastRow = (--t.mSeats.end())->second->mRow;
	auto lastSeatInRow = (--t.mSeats.end())->second->mSeatInRow;
	short seatCounter = 0, vipSeatCounter = 0, childSeatCounter = 0, lastRowSpaces = 0;
	for (auto b = t.mSeats.begin(), e = t.mSeats.end(); b != e; ++b)
	{
		if (b->second->mSeatInRow == 1)
			os << "\b" << std::endl << b->second->mRow << ".\t";
		if (b->second->mRow == lastRow)
		{
			lastRow = {};
			--b;
			lastRowSpaces = b->second->mSeatInRow - lastSeatInRow;
			std::string s(lastRowSpaces, ' ');
			os << s;
			++b;
		}
		if (b->second.get() == dynamic_cast<VipSeat*>(b->second.get()))
		{
			os << "V ";
			//os << static_cast<unsigned char>(255) << " ";
			++vipSeatCounter;
		}
		else
		{
			if (b->second.get() == dynamic_cast<ChildSeat*>(b->second.get())) {
				++childSeatCounter;
				os << "C ";
			}
			else {
				os << "O ";
				++seatCounter;
			}
		}
	}
	std::ostringstream nextLine2;
	os << std::endl << "\n  \t" << std::string(lastRowSpaces, ' ');
	for (size_t i = 1; i <= lastSeatInRow; ++i)
	{
		if (i % 2)
			os << std::left << std::setw(4) << std::to_string(i) + ".";
		else
			nextLine2 << std::left << std::setw(4) << std::to_string(i) + ".";
	}
	os << "\b\n  \t  " << std::string(lastRowSpaces, ' ') << nextLine2.str() << std::endl;
	os << "The theater \"" << t.mName << "\" has " << seatCounter << " ordinary seats, " <<
		vipSeatCounter << " vip seats and " << childSeatCounter << " child seats." << std::endl;
	return t;
}
Theater& change_stake(Theater& t, const float stake)
{
	for (auto s : t.mSeats)
		s.second->changeStake(stake);
	return t;
}
Theater& change_price(Theater& t, const float price)
{
	for (auto s : t.mSeats)
		s.second->changePrice(price);
	return t;
}
Theater& random_fill(Theater& t)
{
	std::uniform_int_distribution<uShort> dist3(0, 2);
	for (auto r : t.mSeats)
	{
		if (!r.second->mBought)
		{

			switch (dist3(Theater::rng))
			{
			case 0u:
				r.second->mBought = true;
				r.second->mWho = t.mName;
				break;
			case 1u:
				r.second->mReserved = true;
				r.second->mWho = t.mName;
				break;
			case 2u:
			default:
				break;
			}

		}

	}


	return t;
}





Theater::Theater(std::string nameOfTheater): mName(nameOfTheater)
{
	uShort seat = 1, row = 1, columns = 10;
	uShort middle = columns / 2;
	for (int g_num = 1 ; g_num <= 100; ++g_num)
	{
		if (row == middle || row == middle + static_cast<uShort>(1))
			mSeats.emplace(g_num, new VipSeat(row, seat));
		else if (row == columns)
			mSeats.emplace(g_num, new ChildSeat(row, seat));
		else
			mSeats.emplace(g_num, new Seat(row, seat));
		++seat;
		if (seat > columns) {
			seat = 1;
			++row;
		}
	}
}
Theater::Theater(std::string nameOfTheater, int allSeats): mName(nameOfTheater)
{
	uShort seat = 1, row = 1, columns =
		static_cast<uShort>(std::ceil(std::sqrt(static_cast<float>(allSeats))));
	uShort lastRow = std::ceil(allSeats / static_cast<float>(columns));
	uShort middle = lastRow / 2;
	for (int g_num = 1; g_num <= allSeats; ++g_num)
	{
		if (row == middle || row == middle + static_cast<uShort>(1))
			mSeats.emplace(g_num, new VipSeat(row, seat));
		else if (row == lastRow)
			mSeats.emplace(g_num, new ChildSeat(row, seat));
		else
			mSeats.emplace(g_num, new Seat(row, seat));
		++seat;
		if (seat > columns) {
			seat = 1;
			++row;
		}
	}
}
Theater::Theater(std::string nameOfTheater, int allSeats, uShort rows):	mName(nameOfTheater)
{
	if (static_cast<uShort>(allSeats) < rows)
	{
		std::cout << "In the theater \"" << mName << "\" rows are less than seats, "
			"theater will be created with rows as much as seats!\n";
		rows = static_cast<uShort>(allSeats);
	}
		uShort seat = 1, row = 1, columns =
			static_cast<uShort>(std::ceil(static_cast<float>(allSeats) / rows));
		const uShort& lastRow = rows;
		uShort middle = lastRow / 2;
		for (int g_num = 1; g_num <= allSeats; ++g_num)
		{
			if (row == middle || row == middle + static_cast<uShort>(1))
				mSeats.emplace(g_num, new VipSeat(row, seat));
			else if (row == rows)
				mSeats.emplace(g_num, new ChildSeat(row, seat));
			else
				mSeats.emplace(g_num, new Seat(row, seat));
			++seat;
			if (seat > columns) {
				seat = 1;
				++row;
			}
		}
		if (mSeats[allSeats]->mRow != rows)
		{
			mSeats[allSeats]->mRow = static_cast<uShort>(rows);
			mSeats[allSeats]->mSeatInRow = static_cast<uShort>(1u);
		}

}
Theater::~Theater()
{ //Используется в случае отсутствия интеллектуальных указателей
	/*
	for (auto it : mSeats) {
		delete it.second;
	}
	*/
}



Theater& Theater::order_ticket(const std::string& yourName, float& wallet, int seat)
{
	return ::order_ticket(*this, yourName, wallet, seat);
}
Theater& Theater::order_ticket(const std::string& yourName, float& wallet, uShort row, uShort rowInSeat)
{
	return ::order_ticket(*this, yourName, wallet, row, rowInSeat);
}
Theater& Theater::order_tickets(const std::string& yourName, float& wallet, std::initializer_list<int> seats)
{
	return ::order_tickets(*this, yourName, wallet, seats);
}

const Theater& Theater::check_seat(int seat)
{
	return ::check_seat(*this, seat);
}
const Theater& Theater::check_seat(uShort row, uShort rowInSeat)
{
	return ::check_seat(*this, row, rowInSeat);
}
const Theater& Theater::check_seats(std::initializer_list<int> seats)
{
	return ::check_seats(*this, seats);
}

Theater& Theater::reserve_seat(const std::string& yourName, int seat)
{
	return ::reserve_seat(*this, yourName, seat);
}
Theater& Theater::reserve_seat(const std::string& yourName, uShort row, uShort rowInSeat)
{
	return ::reserve_seat(*this, yourName, row, rowInSeat);
}
Theater& Theater::reserve_seats(const std::string& yourName, std::initializer_list<int> seats)
{
	return ::reserve_seats(*this, yourName, seats);
}


const Theater& Theater::check_theater_seats(std::ostream& os)
{
	os << *this;
	return *this;
}
const Theater& Theater::check_theater_types_of_seats(std::ostream& os)
{
	return ::check_theater_types_of_seats(os, *this);
}
Theater& Theater::random_fill()
{
	return ::random_fill(*this);
}
Theater& Theater::change_stake(const float price)
{
	return ::change_stake(*this, price);
}
Theater& Theater::change_price(const float price)
{
	return ::change_price(*this, price);
}
std::string Theater::name() const
{
	return mName;
}



std::ostream& operator<<(std::ostream& os, const Theater& t)
{
	os << "The theater \"" << t.mName << "\" has following seats:\n\t(For the last row focus on numbers below)\n  \t";
	std::ostringstream nextLine;
	for (auto topNumbers : t.mSeats)
	{
		if (topNumbers.second->mRow == 2)
			break;
		if (topNumbers.second->mSeatInRow % 2)
			os << std::left << std::setw(4) << std::to_string(topNumbers.second->mSeatInRow) + ".";
		else
			nextLine << std::left << std::setw(4) << std::to_string(topNumbers.second->mSeatInRow) + ".";
	}
	os << "\b\n  \t  " << nextLine.str() << std::endl;

	auto lastRow = (--t.mSeats.end())->second->mRow;
	auto lastSeatInRow = (--t.mSeats.end())->second->mSeatInRow;
	short seatCounterEmpty = 0, seatCounterBought = 0, seatCounterReserved = 0, lastRowSpaces = 0;
	for (auto b = t.mSeats.begin(), e = t.mSeats.end(); b != e; ++b)
	{
		if (b->second->mSeatInRow == 1)
			os << "\b" << std::endl << b->second->mRow << ".\t";
		if (b->second->mRow == lastRow)
		{
			lastRow = {};
			--b;
			lastRowSpaces = b->second->mSeatInRow - lastSeatInRow;
			os << std::string(lastRowSpaces, ' ');
			++b;
		}
		if (b->second->mBought)
		{
			os << "X ";
			++seatCounterBought;
		}
		else
		{
			if (b->second->mReserved) {
				++seatCounterReserved;
				os << "? ";
			}
			else {
				os << "O ";
				++seatCounterEmpty;
			}
		}
	}
	std::ostringstream nextLine2;
	os << std::endl << "\n  \t" << std::string(lastRowSpaces, ' ');
	for (size_t i = 1; i <= lastSeatInRow; ++i)
	{
		if (i % 2)
			os << std::left << std::setw(4) << std::to_string(i) + ".";
		else
			nextLine2 << std::left << std::setw(4) << std::to_string(i) + ".";
	}
	os << "\b\n  \t  " << std::string(lastRowSpaces, ' ')  << nextLine2.str() << std::endl;
	os << "The theater \"" << t.mName << "\" has " << seatCounterEmpty << " empty seats and " <<
		seatCounterBought + seatCounterReserved << " occupied and reserved seats." << std::endl;
	return os;
}