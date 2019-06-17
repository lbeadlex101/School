package com.acme.financial;

import static org.junit.Assert.*;

import org.junit.Test;

public class BankAccountTC {
	
	@Test
	public void testTransfer() throws Exception {
		BankAccount acct1 = new BankAccount(100);
		BankAccount acct2 = new BankAccount(100);
		
		assertNotNull(acct1);
		assertEquals("balance should be 100", 100, acct1.getBalance(), 0.001);
		
		assertNotNull(acct2);
		assertEquals("balance should be 100", 100, acct1.getBalance(), 0.001);
		
		acct1.transfer(25, acct2);
		assertEquals("balance acct1 should be 75", 75, acct1.getBalance(), 0.001);
		assertEquals("balance acct2 should be 125", 125, acct2.getBalance(), 0.001);
	}
	
	@Test
	public void testWithdrawException() throws Exception {
		BankAccount acct1 = new BankAccount(100);
		
		assertNotNull(acct1);
		assertEquals("balance should be 100", 100, acct1.getBalance(), 0.001);
		
		try {
			acct1.withdraw(150);
		} catch (Exception e) {
			assertEquals(e.getMessage(), "insufficient funds");
			return;
		}
	}
		
	@Test
	public void testWithdrawPositiveException() throws Exception {
		BankAccount acct1 = new BankAccount(100);
			
		assertNotNull(acct1);
		assertEquals("balance should be 100", 100, acct1.getBalance(), 0.001);
		
		try {
			acct1.withdraw(50);
		} catch (Exception e) {
			assertEquals("Balance should be 50", 50, acct1.getBalance(), 0.001);
			return;
		}
		
	}
	
	@Test
	public void testDepositException() throws Exception {
		BankAccount acct1 = new BankAccount(100);
		
		assertNotNull(acct1);
		assertEquals("balance should be 100", 100, acct1.getBalance(), 0.001);
		
		try {
			acct1.deposit(-100);
		} catch (Exception e) {
			assertEquals(e.getMessage(), "negative deposit value");
			return;
		}
		
	}
}
