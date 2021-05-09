# IC901_ToneUnit_clone

This project was born of necessity when an IC-901 that I purchased turned up without the stock encoder anywhere to be found.  Since the encoders were stock, there just aren't any to be found on the "e-bay" market, so replacing the missing piece posed a bit of a conundrum.

Borrowing code from my HM133 project, it was pretty easy to come up with a single-chip solution to the issue.  An external crystal is used to hit the precision targets for the CTCSS standards.  The prototype used a standard colorburst crystal of 3.579545 MHz, but a 14.318180 MHz (colorburst x4) seems to be a better choice.  While there is plenty of headroom RE processor speed for this project, the faster crystal makes it easier to operate the PCA peripheral for the CTCSS synthesis and support other operations should one wish to integrate other features into the encoder (such as DPL encoding).

The ICD (Interface Control Document) serves as the initial specification for the project.  A schematic of the prototype along with a couple of photos are included in the HW subfolder.  The code is committed as a Keil project and the ConfigWizardII data file is also included.  A pdf in the HW folder describes the project and hardware/software.
