/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ABORT_P = 258,
     ABSOLUTE_P = 259,
     ACCESS = 260,
     ACTION = 261,
     ADD_P = 262,
     ADMIN = 263,
     AFTER = 264,
     AGGREGATE = 265,
     ALL = 266,
     ALSO = 267,
     ALTER = 268,
     ALWAYS = 269,
     ANALYSE = 270,
     ANALYZE = 271,
     AND = 272,
     ANY = 273,
     ARRAY = 274,
     AS = 275,
     ASC = 276,
     ASSERTION = 277,
     ASSIGNMENT = 278,
     ASYMMETRIC = 279,
     AT = 280,
     AUTHORIZATION = 281,
     BACKWARD = 282,
     BEFORE = 283,
     BEGIN_P = 284,
     BETWEEN = 285,
     BIGINT = 286,
     BINARY = 287,
     BIT = 288,
     BOOLEAN_P = 289,
     BOTH = 290,
     BY = 291,
     CACHE = 292,
     CALLED = 293,
     CASCADE = 294,
     CASCADED = 295,
     CASE = 296,
     CAST = 297,
     CATALOG_P = 298,
     CHAIN = 299,
     CHAR_P = 300,
     CHARACTER = 301,
     CHARACTERISTICS = 302,
     CHECK = 303,
     CHECKPOINT = 304,
     CLASS = 305,
     CLOSE = 306,
     CLUSTER = 307,
     COALESCE = 308,
     COLLATE = 309,
     COLUMN = 310,
     COMMENT = 311,
     COMMIT = 312,
     COMMITTED = 313,
     CONCURRENTLY = 314,
     CONFIGURATION = 315,
     CONNECTION = 316,
     CONSTRAINT = 317,
     CONSTRAINTS = 318,
     CONTENT_P = 319,
     CONTINUE_P = 320,
     CONVERSION_P = 321,
     COPY = 322,
     COST = 323,
     CREATE = 324,
     CREATEDB = 325,
     CREATEROLE = 326,
     CREATEUSER = 327,
     CROSS = 328,
     CSV = 329,
     CURRENT_P = 330,
     CURRENT_CATALOG = 331,
     CURRENT_DATE = 332,
     CURRENT_ROLE = 333,
     CURRENT_SCHEMA = 334,
     CURRENT_TIME = 335,
     CURRENT_TIMESTAMP = 336,
     CURRENT_USER = 337,
     CURSOR = 338,
     CYCLE = 339,
     DATA_P = 340,
     DATABASE = 341,
     DAY_P = 342,
     DEALLOCATE = 343,
     DEC = 344,
     DECIMAL_P = 345,
     DECLARE = 346,
     DEFAULT = 347,
     DEFAULTS = 348,
     DEFERRABLE = 349,
     DEFERRED = 350,
     DEFINER = 351,
     DELETE_P = 352,
     DELIMITER = 353,
     DELIMITERS = 354,
     DESC = 355,
     DICTIONARY = 356,
     DISABLE_P = 357,
     DISCARD = 358,
     DISTINCT = 359,
     DO = 360,
     DOCUMENT_P = 361,
     DOMAIN_P = 362,
     DOUBLE_P = 363,
     DROP = 364,
     EACH = 365,
     ELSE = 366,
     ENABLE_P = 367,
     ENCODING = 368,
     ENCRYPTED = 369,
     END_P = 370,
     ENUM_P = 371,
     ESCAPE = 372,
     EXCEPT = 373,
     EXCLUDING = 374,
     EXCLUSIVE = 375,
     EXECUTE = 376,
     EXISTS = 377,
     EXPLAIN = 378,
     EXTERNAL = 379,
     EXTRACT = 380,
     FALSE_P = 381,
     FAMILY = 382,
     FETCH = 383,
     FIRST_P = 384,
     FLOAT_P = 385,
     FOLLOWING = 386,
     FOR = 387,
     FORCE = 388,
     FOREIGN = 389,
     FORWARD = 390,
     FREEZE = 391,
     FROM = 392,
     FULL = 393,
     FUNCTION = 394,
     GLOBAL = 395,
     GRANT = 396,
     GRANTED = 397,
     GREATEST = 398,
     GROUP_P = 399,
     HANDLER = 400,
     HAVING = 401,
     HEADER_P = 402,
     HOLD = 403,
     HOUR_P = 404,
     IDENTITY_P = 405,
     IF_P = 406,
     ILIKE = 407,
     IMMEDIATE = 408,
     IMMUTABLE = 409,
     IMPLICIT_P = 410,
     IN_P = 411,
     INCLUDING = 412,
     INCREMENT = 413,
     INDEX = 414,
     INDEXES = 415,
     INHERIT = 416,
     INHERITS = 417,
     INITIALLY = 418,
     INNER_P = 419,
     INOUT = 420,
     INPUT_P = 421,
     INSENSITIVE = 422,
     INSERT = 423,
     INSTEAD = 424,
     INT_P = 425,
     INTEGER = 426,
     INTERSECT = 427,
     INTERVAL = 428,
     INTO = 429,
     INVOKER = 430,
     IS = 431,
     ISNULL = 432,
     ISOLATION = 433,
     JOIN = 434,
     KEY = 435,
     LANCOMPILER = 436,
     LANGUAGE = 437,
     LARGE_P = 438,
     LAST_P = 439,
     LC_COLLATE_P = 440,
     LC_CTYPE_P = 441,
     LEADING = 442,
     LEAST = 443,
     LEFT = 444,
     LEVEL = 445,
     LIKE = 446,
     LIMIT = 447,
     LISTEN = 448,
     LOAD = 449,
     LOCAL = 450,
     LOCALTIME = 451,
     LOCALTIMESTAMP = 452,
     LOCATION = 453,
     LOCK_P = 454,
     LOGIN_P = 455,
     MAPPING = 456,
     MATCH = 457,
     MAXVALUE = 458,
     MINUTE_P = 459,
     MINVALUE = 460,
     MODE = 461,
     MONTH_P = 462,
     MOVE = 463,
     NAME_P = 464,
     NAMES = 465,
     NATIONAL = 466,
     NATURAL = 467,
     NCHAR = 468,
     NEW = 469,
     NEXT = 470,
     NO = 471,
     NOCREATEDB = 472,
     NOCREATEROLE = 473,
     NOCREATEUSER = 474,
     NOINHERIT = 475,
     NOLOGIN_P = 476,
     NONE = 477,
     NOSUPERUSER = 478,
     NOT = 479,
     NOTHING = 480,
     NOTIFY = 481,
     NOTNULL = 482,
     NOWAIT = 483,
     NULL_P = 484,
     NULLIF = 485,
     NULLS_P = 486,
     NUMERIC = 487,
     OBJECT_P = 488,
     OF = 489,
     OFF = 490,
     OFFSET = 491,
     OIDS = 492,
     OLD = 493,
     ON = 494,
     ONLY = 495,
     OPERATOR = 496,
     OPTION = 497,
     OPTIONS = 498,
     OR = 499,
     ORDER = 500,
     OUT_P = 501,
     OUTER_P = 502,
     OVER = 503,
     OVERLAPS = 504,
     OVERLAY = 505,
     OWNED = 506,
     OWNER = 507,
     PARSER = 508,
     PARTIAL = 509,
     PARTITION = 510,
     PASSWORD = 511,
     PLACING = 512,
     PLANS = 513,
     POSITION = 514,
     PRECEDING = 515,
     PRECISION = 516,
     PRESERVE = 517,
     PREPARE = 518,
     PREPARED = 519,
     PRIMARY = 520,
     PRIOR = 521,
     PRIVILEGES = 522,
     PROCEDURAL = 523,
     PROCEDURE = 524,
     QUOTE = 525,
     RANGE = 526,
     READ = 527,
     REAL = 528,
     REASSIGN = 529,
     RECHECK = 530,
     RECURSIVE = 531,
     REFERENCES = 532,
     REINDEX = 533,
     RELATIVE_P = 534,
     RELEASE = 535,
     RENAME = 536,
     REPEATABLE = 537,
     REPLACE = 538,
     REPLICA = 539,
     RESET = 540,
     RESTART = 541,
     RESTRICT = 542,
     RETURNING = 543,
     RETURNS = 544,
     REVOKE = 545,
     RIGHT = 546,
     ROLE = 547,
     ROLLBACK = 548,
     ROW = 549,
     ROWS = 550,
     RULE = 551,
     SAVEPOINT = 552,
     SCHEMA = 553,
     SCROLL = 554,
     SEARCH = 555,
     SECOND_P = 556,
     SECURITY = 557,
     SELECT = 558,
     SEQUENCE = 559,
     SERIALIZABLE = 560,
     SERVER = 561,
     SESSION = 562,
     SESSION_USER = 563,
     SET = 564,
     SETOF = 565,
     SHARE = 566,
     SHOW = 567,
     SIMILAR = 568,
     SIMPLE = 569,
     SMALLINT = 570,
     SOME = 571,
     STABLE = 572,
     STANDALONE_P = 573,
     START = 574,
     STATEMENT = 575,
     STATISTICS = 576,
     STDIN = 577,
     STDOUT = 578,
     STORAGE = 579,
     STRICT_P = 580,
     STRIP_P = 581,
     SUBSTRING = 582,
     SUPERUSER_P = 583,
     SYMMETRIC = 584,
     SYSID = 585,
     SYSTEM_P = 586,
     TABLE = 587,
     TABLESPACE = 588,
     TEMP = 589,
     TEMPLATE = 590,
     TEMPORARY = 591,
     TEXT_P = 592,
     THEN = 593,
     TIME = 594,
     TIMESTAMP = 595,
     TO = 596,
     TRAILING = 597,
     TRANSACTION = 598,
     TREAT = 599,
     TRIGGER = 600,
     TRIM = 601,
     TRUE_P = 602,
     TRUNCATE = 603,
     TRUSTED = 604,
     TYPE_P = 605,
     UNBOUNDED = 606,
     UNCOMMITTED = 607,
     UNENCRYPTED = 608,
     UNION = 609,
     UNIQUE = 610,
     UNKNOWN = 611,
     UNLISTEN = 612,
     UNTIL = 613,
     UPDATE = 614,
     USER = 615,
     USING = 616,
     VACUUM = 617,
     VALID = 618,
     VALIDATOR = 619,
     VALUE_P = 620,
     VALUES = 621,
     VARCHAR = 622,
     VARIADIC = 623,
     VARYING = 624,
     VERBOSE = 625,
     VERSION_P = 626,
     VIEW = 627,
     VOLATILE = 628,
     WHEN = 629,
     WHERE = 630,
     WHITESPACE_P = 631,
     WINDOW = 632,
     WITH = 633,
     WITHOUT = 634,
     WORK = 635,
     WRAPPER = 636,
     WRITE = 637,
     XML_P = 638,
     XMLATTRIBUTES = 639,
     XMLCONCAT = 640,
     XMLELEMENT = 641,
     XMLFOREST = 642,
     XMLPARSE = 643,
     XMLPI = 644,
     XMLROOT = 645,
     XMLSERIALIZE = 646,
     YEAR_P = 647,
     YES_P = 648,
     ZONE = 649,
     NULLS_FIRST = 650,
     NULLS_LAST = 651,
     WITH_TIME = 652,
     IDENT = 653,
     FCONST = 654,
     SCONST = 655,
     BCONST = 656,
     XCONST = 657,
     Op = 658,
     ICONST = 659,
     PARAM = 660,
     POSTFIXOP = 661,
     UMINUS = 662,
     TYPECAST = 663
   };
#endif
/* Tokens.  */
#define ABORT_P 258
#define ABSOLUTE_P 259
#define ACCESS 260
#define ACTION 261
#define ADD_P 262
#define ADMIN 263
#define AFTER 264
#define AGGREGATE 265
#define ALL 266
#define ALSO 267
#define ALTER 268
#define ALWAYS 269
#define ANALYSE 270
#define ANALYZE 271
#define AND 272
#define ANY 273
#define ARRAY 274
#define AS 275
#define ASC 276
#define ASSERTION 277
#define ASSIGNMENT 278
#define ASYMMETRIC 279
#define AT 280
#define AUTHORIZATION 281
#define BACKWARD 282
#define BEFORE 283
#define BEGIN_P 284
#define BETWEEN 285
#define BIGINT 286
#define BINARY 287
#define BIT 288
#define BOOLEAN_P 289
#define BOTH 290
#define BY 291
#define CACHE 292
#define CALLED 293
#define CASCADE 294
#define CASCADED 295
#define CASE 296
#define CAST 297
#define CATALOG_P 298
#define CHAIN 299
#define CHAR_P 300
#define CHARACTER 301
#define CHARACTERISTICS 302
#define CHECK 303
#define CHECKPOINT 304
#define CLASS 305
#define CLOSE 306
#define CLUSTER 307
#define COALESCE 308
#define COLLATE 309
#define COLUMN 310
#define COMMENT 311
#define COMMIT 312
#define COMMITTED 313
#define CONCURRENTLY 314
#define CONFIGURATION 315
#define CONNECTION 316
#define CONSTRAINT 317
#define CONSTRAINTS 318
#define CONTENT_P 319
#define CONTINUE_P 320
#define CONVERSION_P 321
#define COPY 322
#define COST 323
#define CREATE 324
#define CREATEDB 325
#define CREATEROLE 326
#define CREATEUSER 327
#define CROSS 328
#define CSV 329
#define CURRENT_P 330
#define CURRENT_CATALOG 331
#define CURRENT_DATE 332
#define CURRENT_ROLE 333
#define CURRENT_SCHEMA 334
#define CURRENT_TIME 335
#define CURRENT_TIMESTAMP 336
#define CURRENT_USER 337
#define CURSOR 338
#define CYCLE 339
#define DATA_P 340
#define DATABASE 341
#define DAY_P 342
#define DEALLOCATE 343
#define DEC 344
#define DECIMAL_P 345
#define DECLARE 346
#define DEFAULT 347
#define DEFAULTS 348
#define DEFERRABLE 349
#define DEFERRED 350
#define DEFINER 351
#define DELETE_P 352
#define DELIMITER 353
#define DELIMITERS 354
#define DESC 355
#define DICTIONARY 356
#define DISABLE_P 357
#define DISCARD 358
#define DISTINCT 359
#define DO 360
#define DOCUMENT_P 361
#define DOMAIN_P 362
#define DOUBLE_P 363
#define DROP 364
#define EACH 365
#define ELSE 366
#define ENABLE_P 367
#define ENCODING 368
#define ENCRYPTED 369
#define END_P 370
#define ENUM_P 371
#define ESCAPE 372
#define EXCEPT 373
#define EXCLUDING 374
#define EXCLUSIVE 375
#define EXECUTE 376
#define EXISTS 377
#define EXPLAIN 378
#define EXTERNAL 379
#define EXTRACT 380
#define FALSE_P 381
#define FAMILY 382
#define FETCH 383
#define FIRST_P 384
#define FLOAT_P 385
#define FOLLOWING 386
#define FOR 387
#define FORCE 388
#define FOREIGN 389
#define FORWARD 390
#define FREEZE 391
#define FROM 392
#define FULL 393
#define FUNCTION 394
#define GLOBAL 395
#define GRANT 396
#define GRANTED 397
#define GREATEST 398
#define GROUP_P 399
#define HANDLER 400
#define HAVING 401
#define HEADER_P 402
#define HOLD 403
#define HOUR_P 404
#define IDENTITY_P 405
#define IF_P 406
#define ILIKE 407
#define IMMEDIATE 408
#define IMMUTABLE 409
#define IMPLICIT_P 410
#define IN_P 411
#define INCLUDING 412
#define INCREMENT 413
#define INDEX 414
#define INDEXES 415
#define INHERIT 416
#define INHERITS 417
#define INITIALLY 418
#define INNER_P 419
#define INOUT 420
#define INPUT_P 421
#define INSENSITIVE 422
#define INSERT 423
#define INSTEAD 424
#define INT_P 425
#define INTEGER 426
#define INTERSECT 427
#define INTERVAL 428
#define INTO 429
#define INVOKER 430
#define IS 431
#define ISNULL 432
#define ISOLATION 433
#define JOIN 434
#define KEY 435
#define LANCOMPILER 436
#define LANGUAGE 437
#define LARGE_P 438
#define LAST_P 439
#define LC_COLLATE_P 440
#define LC_CTYPE_P 441
#define LEADING 442
#define LEAST 443
#define LEFT 444
#define LEVEL 445
#define LIKE 446
#define LIMIT 447
#define LISTEN 448
#define LOAD 449
#define LOCAL 450
#define LOCALTIME 451
#define LOCALTIMESTAMP 452
#define LOCATION 453
#define LOCK_P 454
#define LOGIN_P 455
#define MAPPING 456
#define MATCH 457
#define MAXVALUE 458
#define MINUTE_P 459
#define MINVALUE 460
#define MODE 461
#define MONTH_P 462
#define MOVE 463
#define NAME_P 464
#define NAMES 465
#define NATIONAL 466
#define NATURAL 467
#define NCHAR 468
#define NEW 469
#define NEXT 470
#define NO 471
#define NOCREATEDB 472
#define NOCREATEROLE 473
#define NOCREATEUSER 474
#define NOINHERIT 475
#define NOLOGIN_P 476
#define NONE 477
#define NOSUPERUSER 478
#define NOT 479
#define NOTHING 480
#define NOTIFY 481
#define NOTNULL 482
#define NOWAIT 483
#define NULL_P 484
#define NULLIF 485
#define NULLS_P 486
#define NUMERIC 487
#define OBJECT_P 488
#define OF 489
#define OFF 490
#define OFFSET 491
#define OIDS 492
#define OLD 493
#define ON 494
#define ONLY 495
#define OPERATOR 496
#define OPTION 497
#define OPTIONS 498
#define OR 499
#define ORDER 500
#define OUT_P 501
#define OUTER_P 502
#define OVER 503
#define OVERLAPS 504
#define OVERLAY 505
#define OWNED 506
#define OWNER 507
#define PARSER 508
#define PARTIAL 509
#define PARTITION 510
#define PASSWORD 511
#define PLACING 512
#define PLANS 513
#define POSITION 514
#define PRECEDING 515
#define PRECISION 516
#define PRESERVE 517
#define PREPARE 518
#define PREPARED 519
#define PRIMARY 520
#define PRIOR 521
#define PRIVILEGES 522
#define PROCEDURAL 523
#define PROCEDURE 524
#define QUOTE 525
#define RANGE 526
#define READ 527
#define REAL 528
#define REASSIGN 529
#define RECHECK 530
#define RECURSIVE 531
#define REFERENCES 532
#define REINDEX 533
#define RELATIVE_P 534
#define RELEASE 535
#define RENAME 536
#define REPEATABLE 537
#define REPLACE 538
#define REPLICA 539
#define RESET 540
#define RESTART 541
#define RESTRICT 542
#define RETURNING 543
#define RETURNS 544
#define REVOKE 545
#define RIGHT 546
#define ROLE 547
#define ROLLBACK 548
#define ROW 549
#define ROWS 550
#define RULE 551
#define SAVEPOINT 552
#define SCHEMA 553
#define SCROLL 554
#define SEARCH 555
#define SECOND_P 556
#define SECURITY 557
#define SELECT 558
#define SEQUENCE 559
#define SERIALIZABLE 560
#define SERVER 561
#define SESSION 562
#define SESSION_USER 563
#define SET 564
#define SETOF 565
#define SHARE 566
#define SHOW 567
#define SIMILAR 568
#define SIMPLE 569
#define SMALLINT 570
#define SOME 571
#define STABLE 572
#define STANDALONE_P 573
#define START 574
#define STATEMENT 575
#define STATISTICS 576
#define STDIN 577
#define STDOUT 578
#define STORAGE 579
#define STRICT_P 580
#define STRIP_P 581
#define SUBSTRING 582
#define SUPERUSER_P 583
#define SYMMETRIC 584
#define SYSID 585
#define SYSTEM_P 586
#define TABLE 587
#define TABLESPACE 588
#define TEMP 589
#define TEMPLATE 590
#define TEMPORARY 591
#define TEXT_P 592
#define THEN 593
#define TIME 594
#define TIMESTAMP 595
#define TO 596
#define TRAILING 597
#define TRANSACTION 598
#define TREAT 599
#define TRIGGER 600
#define TRIM 601
#define TRUE_P 602
#define TRUNCATE 603
#define TRUSTED 604
#define TYPE_P 605
#define UNBOUNDED 606
#define UNCOMMITTED 607
#define UNENCRYPTED 608
#define UNION 609
#define UNIQUE 610
#define UNKNOWN 611
#define UNLISTEN 612
#define UNTIL 613
#define UPDATE 614
#define USER 615
#define USING 616
#define VACUUM 617
#define VALID 618
#define VALIDATOR 619
#define VALUE_P 620
#define VALUES 621
#define VARCHAR 622
#define VARIADIC 623
#define VARYING 624
#define VERBOSE 625
#define VERSION_P 626
#define VIEW 627
#define VOLATILE 628
#define WHEN 629
#define WHERE 630
#define WHITESPACE_P 631
#define WINDOW 632
#define WITH 633
#define WITHOUT 634
#define WORK 635
#define WRAPPER 636
#define WRITE 637
#define XML_P 638
#define XMLATTRIBUTES 639
#define XMLCONCAT 640
#define XMLELEMENT 641
#define XMLFOREST 642
#define XMLPARSE 643
#define XMLPI 644
#define XMLROOT 645
#define XMLSERIALIZE 646
#define YEAR_P 647
#define YES_P 648
#define ZONE 649
#define NULLS_FIRST 650
#define NULLS_LAST 651
#define WITH_TIME 652
#define IDENT 653
#define FCONST 654
#define SCONST 655
#define BCONST 656
#define XCONST 657
#define Op 658
#define ICONST 659
#define PARAM 660
#define POSTFIXOP 661
#define UMINUS 662
#define TYPECAST 663




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 162 "gram.y"
{
	int					ival;
	char				chr;
	char				*str;
	const char			*keyword;
	bool				boolean;
	JoinType			jtype;
	DropBehavior		dbehavior;
	OnCommitAction		oncommit;
	List				*list;
	Node				*node;
	Value				*value;
	ObjectType			objtype;

	TypeName			*typnam;
	FunctionParameter   *fun_param;
	FunctionParameterMode fun_param_mode;
	FuncWithArgs		*funwithargs;
	DefElem				*defelt;
	SortBy				*sortby;
	WindowDef			*windef;
	JoinExpr			*jexpr;
	IndexElem			*ielem;
	Alias				*alias;
	RangeVar			*range;
	IntoClause			*into;
	WithClause			*with;
	A_Indices			*aind;
	ResTarget			*target;
	struct PrivTarget	*privtarget;
	AccessPriv			*accesspriv;

	InsertStmt			*istmt;
	VariableSetStmt		*vsetstmt;
}
/* Line 1529 of yacc.c.  */
#line 901 "gram.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE base_yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE base_yylloc;
