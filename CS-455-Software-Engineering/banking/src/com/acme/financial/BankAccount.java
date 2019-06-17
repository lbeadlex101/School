package com.acme.financial;

public class BankAccount {
	private double balance;
	
	public BankAccount(double balance) {
		this.balance = balance;
	}
	
	public double getBalance() {
		return balance;
	}
	
	public void withdraw(double amt) throws Exception {
		if(amt > balance) {
			throw new Exception("insufficient funds");
		}
		
		balance -= amt;
	}
	
	public void deposit(double amt) throws Exception {
		if(amt < 0) {
			throw new Exception("negative deposit value");
		}
		
		balance += amt;
	}
	
	public void transfer(double amt, BankAccount other) throws Exception {
		if(balance < amt) {
			throw new Exception("balance < amount");
		}
		
		balance -= amt;
		other.balance += amt;
		
	}
}
