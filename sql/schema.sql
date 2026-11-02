-- Optional: the program creates these tables itself on first run.
-- Run this manually (psql or pgAdmin) only if you prefer to set things up by hand.
--
--   CREATE DATABASE gearhub;   -- run once, connected to the default "postgres" database
--   \c gearhub

CREATE TABLE IF NOT EXISTS brands (
    id   SERIAL PRIMARY KEY,
    name VARCHAR(50) NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS products (
    id             INTEGER PRIMARY KEY,
    name           VARCHAR(100) NOT NULL,
    category       VARCHAR(50)  NOT NULL,
    brand          VARCHAR(50)  NOT NULL REFERENCES brands(name),
    price          NUMERIC(12,2) NOT NULL CHECK (price >= 0),
    stock_quantity INTEGER NOT NULL CHECK (stock_quantity >= 0)
);

CREATE TABLE IF NOT EXISTS checkout_log (
    id         SERIAL PRIMARY KEY,
    product_id INTEGER NOT NULL REFERENCES products(id),
    quantity   INTEGER NOT NULL CHECK (quantity > 0),
    action     VARCHAR(10) NOT NULL CHECK (action IN ('CHECKOUT', 'UNDO')),
    created_at TIMESTAMPTZ NOT NULL DEFAULT now()
);
