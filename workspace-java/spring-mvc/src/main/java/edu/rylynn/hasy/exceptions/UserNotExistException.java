package edu.rylynn.hasy.exceptions;

public class UserNotExistException extends Exception {
	public UserNotExistException()
	{
		
	}
	
	public UserNotExistException(String message)
	{
		super(message);
	}
}
