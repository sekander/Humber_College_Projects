-- LAB 8 CRUD
-- Put your answers on the lines after each letter. E.g. your query for question 1A should go on line 5; your query for question 1B should go on line 7...

-- 1 
-- A 
CREATE TABLE CUSTOMER (
    EMAIL VARCHAR(100) PRIMARY KEY,
    NAME VARCHAR(100) NOT NULL
);

-- B 
CREATE TABLE SUPPLIER (
    SUPPLIER_ID INT PRIMARY KEY,
    NAME VARCHAR(100) NOT NULL,
    LOCATION VARCHAR(100) NOT NULL
);

-- C 
CREATE TABLE `ORDER` (
    ORDER_ID INT PRIMARY KEY,
    EMAIL VARCHAR(100) NOT NULL
);

-- D
CREATE TABLE PRODUCT (
    PRODUCT_ID INT PRIMARY KEY,
    NAME VARCHAR(100) NOT NULL,
    PRICE INT NOT NULL,
    BRAND VARCHAR(100) NOT NULL,
    SUPPLIER_ID INT NOT NULL
);

-- E 
CREATE TABLE ORDER_PRODUCT (
    ORDER_ID INT,
    PRODUCT_ID INT,
    PRIMARY KEY (ORDER_ID, PRODUCT_ID)
);

-- 2 
-- A 
INSERT INTO CUSTOMER (EMAIL, NAME) VALUES 
    ("john@gmail.com", "John"), 
    ("jane@gmail.com", "Jane"), 
    ("alice@gmail.com", "Alice");

-- B 
INSERT INTO SUPPLIER (SUPPLIER_ID, NAME, LOCATION) VALUES 
    (1, "XYZ Electronics", "Toronto"),
    (2, "ABC Gadgets", "Montreal"),
    (3, "XYZ Furniture", "Vancouver");

-- C 
INSERT INTO `ORDER` (ORDER_ID, EMAIL) VALUES 
    (1, "john@gmail.com"),
    (2, "jane@gmail.com"),
    (3, "john@gmail.com"),
    (4, "alice@gmail.com");

-- D
INSERT INTO PRODUCT (PRODUCT_ID, NAME, PRICE, BRAND, SUPPLIER_ID) VALUES 
    (1, "Laptop", 800, "Dell", 1),
    (2, "Smartphone", 600, "Apple", 2),
    (3, "Smartphone", 600, "Samsung", 2),
    (4, "Camera", 300, "Canon", 1),
    (5, "Chair", 100, "Herman Miller", 3);

-- E 
INSERT INTO ORDER_PRODUCT (ORDER_ID, PRODUCT_ID) VALUES 
    (1, 1),
    (2, 2),
    (2, 3),
    (3, 4),
    (4, 5);

-- 3 
-- A 
ALTER TABLE PRODUCT 
ADD CONSTRAINT CHECK_PRICE_FOR_POSITIVE_VALUE CHECK (PRICE >= 0);

-- B 
UPDATE ORDER_PRODUCT 
SET PRODUCT_ID = 4 
WHERE ORDER_ID = 2 AND PRODUCT_ID = 2;

-- 4 
-- A 
DELETE FROM ORDER_PRODUCT 
WHERE ORDER_ID IN (1, 3);

-- B 
DELETE FROM `ORDER` 
WHERE ORDER_ID IN (1, 3);

-- Bonus
-- A 

-- B 

-- C 

