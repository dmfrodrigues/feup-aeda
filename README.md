# Transportes SML {#mainpage}

[Guiding lines](https://moodle.up.pt/pluginfile.php/46150/mod_page/content/35/aeda1920_trabalhosParte1.pdf)

## Requirements

- [x] Use adequate classes to represent the entities envolved
- [x] The classes should have attributes that are adequate to caracterizing the most important concepts of the entities
- [x] Consider adequate relations between classes
- [x] Use the concepts of inheritance and polymorphism
- [x] User data should be saved in files, to use in future executions
- [ ] Conveniently treat possible exceptions
- [x] Use search and sorting algorithms
- [ ] Implemented classes should be documented
- [ ] Allow for basic operations CRUD (create, read, update, delete)
- [x] Use linear structures to manage entities
- [x] Allow for total and partial listings with user-defined criteria
- [x] Use different ordering criteria in the listings
- [ ] Clients can request a service, with origin, destination, travel time,...
- [ ] List the monthly values the company gets from all its transports, from a given truck, and from all trucks of a given kind.
- [x] List clients
- [ ] List services

## ToDo

### Most priority

#### Entities
- [ ] Login for clients, managers and drivers
- [ ] Add, remove and edit truck
- [ ] Add, remove and edit client, manager and driver
- [ ] Allow clients and managers to add services
- [ ] Show list of clients
- [ ] Show list of trucks
- [ ] Show to a driver a list of his services

#### Services
- [ ] Allocate services to trucks and drivers in the most efficient way (less expenses):
- To the driver with the least salary (if drivers have different salaries)
- To the truck that has the lowest expenses
- [x] When a driver arrives to a place, he needs to have someone's contact for loading/unloading, which might or might not be the client for whom the service is being made
- [ ] Issue payment bills when a service is introduced
- [ ] List of completed services and future services

#### Other stuff
- [ ] The salary of a driver depends on the time he works (including his weekly extra hours)
- [ ] A truck can be broken or break during transport
- [ ] When a truck breaks, send it to repair
- [ ] Allow for adding expenses for repairing, taxes, truck taxes, building taxes, for them to show up in accountability

### Mid priority

- [ ] NumberPlate is identified by Number and Country
- [ ] Allocate services to trucks and drivers in the most efficient way (less expenses):
- To the driver with the least qualifications
- To the truck that has traveled the least
- [ ] A service includes a list of predicted actions: load, unload and travel (and each of the actions has an expected time range, and real time range)
- [ ] Get notification when a truck needs periodic inspection
- [ ] If a service is requested for the same day, the next day, the following week or the following month, different prices should be charged. The same way, drivers' salaries depend on the way services were allocated
- [ ] Issue credit notes (when bill is incorrect)
- [ ] Accountability should include salaries, fines, repairs, gas expenses, etc.
- [ ] Show profits and expenses periodically (weekly, monthly, yearly)

### Least priority

- [ ] Ask all clients to update their data in the app
- [ ] Send automatic emails for people to update their data
- [ ] Send promotions emails
- [ ] Notify driver of new services allocated to him
- [ ] Allow one to know the location of a given truck
- [ ] When a driver leaves a place or performs a task (load, unload, take truck for repair), he should notify the company through the app
- [ ] Issue transport permit and send it to *Autoridade Tributária* when a driver intends to leave to transport a good
- [ ] A driver can ask for vacations. Make appropriate checks.
- [ ] A client can reject a delivery. A driver can also notify the app that the client rejected the delivery. Info must be cross-checked and verified to see if they match
