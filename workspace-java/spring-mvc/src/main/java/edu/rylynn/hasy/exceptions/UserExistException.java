package edu.rylynn.hasy.exceptions;

public class UserExistException extends Exception{
	public UserExistException()
	{
		
	}
	
	public UserExistException(String message)
	{
		super(message);
	}
}
