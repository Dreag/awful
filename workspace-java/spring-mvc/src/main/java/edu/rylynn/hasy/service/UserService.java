package edu.rylynn.hasy.service;

import java.util.List;

import edu.rylynn.hasy.entity.User;
import edu.rylynn.hasy.exceptions.UserExistException;
import edu.rylynn.hasy.exceptions.UserNotExistException;

public interface UserService {
	public void registerUser(User user) throws UserExistException;

	public User findUserByUsername(String Username) throws UserNotExistException;

	public boolean checkPassword(String username, String password) throws UserNotExistException;

	public void ChangePassword(String username, String oldpassword, String newpassword) throws UserNotExistException;

	public long queryAccount(String username) throws UserNotExistException;
	
	public void updateUser(User newuser);
	
	public List<User> findAllUser();
}
