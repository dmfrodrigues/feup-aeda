# Hierarchy

## Person
* Name
* Address
* VAT
* Cell phone number(s)

## Address
* Street, house number
* Postal code
* City (in Caps)
* District/Province/State
* Country

## Company
* Is a person
* List of trucks
* List of clients
* List of employees
* List of services
* List of bills

### Truck
* Log of truck events (repairings, inspections,...)
* Maximum transport capacity
* Price
* Maximum reach
* Taxes

#### Refrigerator truck
* Temperature range

#### Dangerous cargo truck
* Danger level
* Can transport solids, liquids or gas?

#### Animals truck

#### Normal truck

### Client
* Is a person

### Employee
* Is a person

#### Manager
* Is an employee
* Salary

#### Driver
* Is an employee
* Salary

### Service
* Cargo type
* Cargo ammount
* Cargo danger level
* Trucks to transport
* List of actions
* Bill pointer

#### Action

* Time it takes to make that action

enum:

* Load
* Unload
* Travel
* Stop/break
* Truck breaks down
* Driver is unavailable

### Bill

* Service provider (the company)
* Service recipient
* What services are being charged, and at what values
* Taxes
* Notify *Autoridade Tributária*
