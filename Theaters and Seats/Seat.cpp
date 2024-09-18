#include "Seat.hpp"
#include <string>
#include <iostream>

Seat::Seat() :mRow(0), mSeatInRow(0), mBought(false), mReserved(false), mWho("Empty"), mPrice(9.99f) {}
Seat::Seat(uShort row, uShort seat) : mRow(row), mSeatInRow(seat), mBought(false), mReserved(false), mWho("Empty"), mPrice(9.99f) {};


VipSeat::VipSeat() : Seat(), mStake(2.0f)  { mPrice *= mStake; };
VipSeat::VipSeat(uShort row, uShort seat) : Seat(row, seat), mStake(2.0f) { mPrice *= mStake; };

ChildSeat::ChildSeat() : Seat(), mDiscount(0.5f) { mPrice *= mDiscount; };
ChildSeat::ChildSeat(uShort row, uShort seat) : Seat(row, seat), mDiscount(0.5f) { mPrice = mPrice * mDiscount; };


Seat& Seat::operator=(const Seat& another) {
	mRow = another.mRow;
	mSeatInRow = another.mSeatInRow;
	mBought = another.mBought;
	mReserved = another.mReserved;
	mWho = another.mWho;
	return *this;
}

Seat& Seat::operator=(Seat&& another) noexcept {
	if (this != &another) {
		mRow = another.mRow;
		mSeatInRow = another.mSeatInRow;
		mBought = another.mBought;
		mReserved = another.mReserved;
		mWho = another.mWho;


		another.mRow = static_cast<uShort>(0);
		another.mSeatInRow = static_cast<uShort>(0);
		another.mBought = false;
		another.mReserved = false;
		another.mWho = "";
	}

	return *this;
}
VipSeat& VipSeat::operator=(const VipSeat& another) {
	Seat::operator=(another);
	mStake = another.mStake;
	return *this;
}

VipSeat& VipSeat::operator=(VipSeat&& another) noexcept {
	if (this != &another) {
		Seat::operator=(std::move(another));
		mStake = another.mStake;

		another.mStake = 0.0f;
	}

	return *this;
}

ChildSeat& ChildSeat::operator=(const ChildSeat& another) {
	Seat::operator=(another);
	mDiscount = another.mDiscount;
	return *this;
}

ChildSeat& ChildSeat::operator=(ChildSeat&& another) noexcept {
	if (this != &another) {
		Seat::operator=(std::move(another));
		mDiscount = another.mDiscount;

		another.mDiscount = 0.0f;
	}

	return *this;
}




Seat& Seat::changePrice(float price)
{
	mPrice = price;
	return *this;
}

Seat& Seat::changeStake(float stake)
{
	// Виртуальная функция меняет ставку только
	// Вип и Детским сиденьям. Обычным - ничего не делает
	return *this;
}

const std::string Seat::whatSeat()
{
	const std::string wS = "Seat";
	return wS;
}

Seat& VipSeat::changePrice(float price)
{
	mPrice = price * mStake;
	return *this;
}

Seat& VipSeat::changeStake(float stake)
{
	mStake = stake;
	return *this;
}

const std::string VipSeat::whatSeat()
{
	const std::string wS = "Vip seat";
	return wS;
}

Seat& ChildSeat::changePrice(float price)
{
	mPrice = price * mDiscount;
	return *this;
}

Seat& ChildSeat::changeStake(float stake)
{
	mDiscount = 1 / stake;
	return *this;
}

const std::string ChildSeat::whatSeat()
{
	const std::string wS = "Child seat";
	return wS;
}
