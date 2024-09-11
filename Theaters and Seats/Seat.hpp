#pragma once

#include <iosfwd>
#include <string>

#include <map>

//Возможно для использования в будущем
enum SEAT {
	ORDINARYSEAT,
	VIPSEAT,
	CHILDSEAT
};

typedef unsigned short uShort;

class Theater;

struct Seat
{
	friend class Theater;

	friend std::ostream& operator<<(std::ostream&, const Theater&);

	friend Theater& order_ticket(Theater&, const std::string& yourName, float& wallet, int seat);
	friend Theater& order_ticket(Theater&, const std::string& yourName, float& wallet, uShort row, uShort rowInSeat);
	friend Theater& order_tickets(Theater&, const std::string& yourName, float& wallet, std::initializer_list<int> seats);
	friend const Theater& check_seat(const Theater&, int seat);
	friend const Theater& check_seat(const Theater&, uShort row, uShort rowInSeat);
	friend const Theater& check_seats(const Theater&, std::initializer_list<int> seats);
	friend Theater& reserve_seat(Theater&, const std::string& yourName, int seat);
	friend Theater& reserve_seat(Theater&, const std::string& yourName, uShort row, uShort rowInSeat);
	friend Theater& reserve_seats(Theater&, const std::string& yourName, std::initializer_list<int> seats);

	friend const Theater& check_theater_types_of_seats(std::ostream& os, const Theater& t);

	friend Theater& change_stake(Theater&, const float stake);
	friend Theater& change_price(Theater&, const float price);

	friend Theater& random_fill(Theater&);

	Seat();
	Seat(uShort, uShort);

	virtual ~Seat() = default;
 protected:

	Seat(const Seat&) = default;
	Seat(Seat&&) = default;

	Seat& operator=(const Seat&);
	Seat& operator=(Seat&&) noexcept;

	virtual Seat& changePrice(float);
	virtual Seat& changeStake(float);

	virtual const std::string whatSeat();

	bool mReserved;
	bool mBought;
	uShort mRow;
	uShort mSeatInRow;
	std::string mWho;
	float mPrice;
};

struct VipSeat final: Seat {

	friend class Theater;

	 VipSeat();
	 VipSeat(uShort, uShort);
 private:


	 VipSeat(const VipSeat&) = default;
	 VipSeat(VipSeat&&) = default;

	 VipSeat& operator=(const VipSeat&);
	 VipSeat& operator=(VipSeat&&) noexcept;

	 Seat& changePrice(float) override;
	 Seat& changeStake(float) override;

	 const std::string whatSeat() override;

	 float mStake;
};


struct ChildSeat final: Seat {

	friend class Theater;

	ChildSeat();
	ChildSeat(uShort, uShort);
private:


	ChildSeat(const ChildSeat&) = default;
	ChildSeat(ChildSeat&&) = default;

	ChildSeat& operator=(const ChildSeat&);
	ChildSeat& operator=(ChildSeat&&) noexcept;

	Seat& changePrice(float) override;
	Seat& changeStake(float) override;

	const std::string whatSeat() override;

	float mDiscount;
};